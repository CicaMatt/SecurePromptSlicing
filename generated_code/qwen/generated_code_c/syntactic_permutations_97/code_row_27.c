#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>
#include <openssl/sha.h>

#define DB_NAME "users.db"

void hash_password(const char *password, char *hash) {
    unsigned char digest[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, password, strlen(password));
    SHA256_Final(digest, &sha256);
    for (int i = 0; i < SHA256_DIGEST_LENGTH; ++i) {
        sprintf(&hash[i * 2], "%02x", (unsigned int)digest[i]);
    }
}

int callback(void *NotUsed, int argc, char **argv, char **azColName) {
    return 1;
}

int main() {
    sqlite3 *db;
    char *zErrMsg = 0;
    int rc;

    rc = sqlite3_open(DB_NAME, &db);
    if (rc) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return 1;
    }

    const char* sql_create_table = 
        "CREATE TABLE IF NOT EXISTS users("
        "id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "username TEXT NOT NULL UNIQUE,"
        "password_hash TEXT NOT NULL,"
        "first_name TEXT,"
        "last_name TEXT,"
        "email TEXT"
        ");";

    rc = sqlite3_exec(db, sql_create_table, callback, 0, &zErrMsg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
        sqlite3_close(db);
        return 1;
    }

    char username[50], password[50], first_name[50], last_name[50], email[50];
    printf("Enter Username: ");
    scanf("%49s", username);
    printf("Enter Password: ");
    scanf("%49s", password);
    printf("Enter First Name: ");
    scanf("%49s", first_name);
    printf("Enter Last Name: ");
    scanf("%49s", last_name);
    printf("Enter Email: ");
    scanf("%49s", email);

    char hashed_password[SHA256_DIGEST_LENGTH * 2 + 1];
    hash_password(password, hashed_password);

    char query_check_user[300];
    snprintf(query_check_user, sizeof(query_check_user), "SELECT * FROM users WHERE username = '%q';", username);
    
    int user_exists;
    rc = sqlite3_exec(db, query_check_user, callback, &user_exists, &zErrMsg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
        sqlite3_close(db);
        return 1;
    }

    if (user_exists) {
        printf("Username already exists.\n");
    } else {
        char query_insert_user[400];
        snprintf(query_insert_user, sizeof(query_insert_user),
                 "INSERT INTO users(username, password_hash, first_name, last_name, email) VALUES('%q', '%q', '%q', '%q', '%q');",
                 username, hashed_password, first_name, last_name, email);

        rc = sqlite3_exec(db, query_insert_user, callback, 0, &zErrMsg);
        if (rc != SQLITE_OK) {
            fprintf(stderr, "SQL error: %s\n", zErrMsg);
            sqlite3_free(zErrMsg);
            sqlite3_close(db);
            return 1;
        }
        printf("Registration succeeded.\n");
    }

    sqlite3_close(db);
    return 0;
}