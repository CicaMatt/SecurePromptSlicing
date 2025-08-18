#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>
#include <openssl/sha.h>

#define DB_NAME "users.db"
#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 100
#define MAX_FIRSTNAME_LENGTH 50
#define MAX_LASTNAME_LENGTH 50
#define MAX_EMAIL_LENGTH 100
#define HASH_SIZE SHA256_DIGEST_LENGTH

void hash_password(const char* password, unsigned char* hash) {
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, password, strlen(password));
    SHA256_Final(hash, &sha256);
}

int main() {
    char username[MAX_USERNAME_LENGTH], password[MAX_PASSWORD_LENGTH];
    char firstname[MAX_FIRSTNAME_LENGTH], lastname[MAX_LASTNAME_LENGTH];
    char email[MAX_EMAIL_LENGTH];
    unsigned char hashed_password[HASH_SIZE];

    printf("Enter Username: ");
    scanf("%s", username);

    printf("Enter Password: ");
    scanf("%s", password);

    printf("Enter First Name: ");
    scanf("%s", firstname);

    printf("Enter Last Name: ");
    scanf("%s", lastname);

    printf("Enter Email: ");
    scanf("%s", email);

    hash_password(password, hashed_password);

    sqlite3 *db;
    char *err_msg = 0;

    int rc = sqlite3_open(DB_NAME, &db);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 1;
    }

    const char* create_table_sql = 
        "CREATE TABLE IF NOT EXISTS users("
        "id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "username TEXT NOT NULL UNIQUE,"
        "password BLOB NOT NULL,"
        "firstname TEXT NOT NULL,"
        "lastname TEXT NOT NULL,"
        "email TEXT NOT NULL"
        ");";

    rc = sqlite3_exec(db, create_table_sql, 0, 0, &err_msg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", err_msg);
        sqlite3_free(err_msg);
        sqlite3_close(db);
        return 1;
    }

    char sql[500];
    snprintf(sql, sizeof(sql), 
             "SELECT * FROM users WHERE username='%s';", username);

    rc = sqlite3_exec(db, sql, 0, 0, &err_msg);
    if (rc == SQLITE_ROW) {
        printf("Username already exists.\n");
    } else {
        snprintf(sql, sizeof(sql),
                 "INSERT INTO users(username, password, firstname, lastname, email)"
                 "VALUES('%s', ?, '%s', '%s', '%s');",
                 username, firstname, lastname, email);

        sqlite3_stmt *stmt;
        rc = sqlite3_prepare_v2(db, sql, -1, &stmt, 0);
        if (rc != SQLITE_OK) {
            fprintf(stderr, "Failed to prepare statement: %s\n", sqlite3_errmsg(db));
            sqlite3_close(db);
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
    }

    sqlite3_close(db);
    return 0;
}