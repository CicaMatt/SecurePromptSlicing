#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>
#include <openssl/sha.h>

#define MAX_USERNAME_LEN 50
#define MAX_PASSWORD_LEN 50
#define MAX_NAME_LEN 50
#define MAX_EMAIL_LEN 100
#define HASH_SIZE SHA256_DIGEST_LENGTH

void hash_password(const char *password, unsigned char *hash) {
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, password, strlen(password));
    SHA256_Final(hash, &sha256);
}

int callback(void *NotUsed, int argc, char **argv, char **azColName) {
    return 1; // If a row is found, return 1
}

int main() {
    sqlite3 *db;
    char *err_message = 0;

    int rc = sqlite3_open("users.db", &db);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        return 1;
    }

    const char *create_table_sql = "CREATE TABLE IF NOT EXISTS users("
                                   "username TEXT PRIMARY KEY,"
                                   "password_hash BLOB,"
                                   "first_name TEXT,"
                                   "last_name TEXT,"
                                   "email TEXT);";

    rc = sqlite3_exec(db, create_table_sql, 0, 0, &err_message);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", err_message);
        sqlite3_free(err_message);
        return 1;
    }

    char username[MAX_USERNAME_LEN];
    char password[MAX_PASSWORD_LEN];
    char first_name[MAX_NAME_LEN];
    char last_name[MAX_NAME_LEN];
    char email[MAX_EMAIL_LEN];

    printf("Enter Username: ");
    scanf("%s", username);

    printf("Enter Password: ");
    scanf("%s", password);

    printf("Enter First Name: ");
    scanf("%s", first_name);

    printf("Enter Last Name: ");
    scanf("%s", last_name);

    printf("Enter Email: ");
    scanf("%s", email);

    unsigned char hashed_password[HASH_SIZE];
    hash_password(password, hashed_password);

    char *query = sqlite3_mprintf("SELECT 1 FROM users WHERE username='%q';", username);
    int user_exists = sqlite3_exec(db, query, callback, 0, &err_message);
    sqlite3_free(query);

    if (user_exists == SQLITE_ROW) {
        printf("Username already exists.\n");
    } else {
        char *insert_sql = sqlite3_mprintf(
            "INSERT INTO users (username, password_hash, first_name, last_name, email) "
            "VALUES ('%q', ?, '%q', '%q', '%q');",
            username, first_name, last_name, email);

        sqlite3_stmt *stmt;
        rc = sqlite3_prepare_v2(db, insert_sql, -1, &stmt, 0);
        if (rc != SQLITE_OK) {
            fprintf(stderr, "SQL error: %s\n", sqlite3_errmsg(db));
            sqlite3_free(insert_sql);
            return 1;
        }

        sqlite3_bind_blob(stmt, 1, hashed_password, HASH_SIZE, SQLITE_STATIC);

        rc = sqlite3_step(stmt);
        if (rc == SQLITE_DONE) {
            printf("Registration succeeded.\n");
        } else {
            fprintf(stderr, "SQL error: %s\n", sqlite3_errmsg(db));
        }

        sqlite3_finalize(stmt);
        sqlite3_free(insert_sql);
    }

    sqlite3_close(db);
    return 0;
}