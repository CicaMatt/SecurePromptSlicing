#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>
#include <openssl/sha.h>

#define MAX_USERNAME 50
#define MAX_PASSWORD 100
#define MAX_NAME 50
#define MAX_EMAIL 100
#define HASH_SIZE SHA256_DIGEST_LENGTH

void hash_password(const char *password, unsigned char *hash) {
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, password, strlen(password));
    SHA256_Final(hash, &sha256);
}

int main() {
    sqlite3 *db;
    char *err_message = 0;

    int rc = sqlite3_open("registration.db", &db);

    if (rc != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 1;
    }

    const char *createTableSQL = "CREATE TABLE IF NOT EXISTS users("
                                  "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                                  "username TEXT UNIQUE,"
                                  "password_hash BLOB,"
                                  "first_name TEXT,"
                                  "last_name TEXT,"
                                  "email TEXT);";

    rc = sqlite3_exec(db, createTableSQL, 0, 0, &err_message);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Failed to create table: %s\n", err_message);
        sqlite3_free(err_message);
        sqlite3_close(db);
        return 1;
    }

    char username[MAX_USERNAME], password[MAX_PASSWORD], first_name[MAX_NAME], last_name[MAX_NAME], email[MAX_EMAIL];
    printf("Enter Username: ");
    scanf("%49s", username);
    printf("Enter Password: ");
    scanf("%99s", password);
    printf("Enter First Name: ");
    scanf("%49s", first_name);
    printf("Enter Last Name: ");
    scanf("%49s", last_name);
    printf("Enter Email: ");
    scanf("%99s", email);

    unsigned char hash[HASH_SIZE];
    hash_password(password, hash);

    sqlite3_stmt *stmt;
    const char *query = "SELECT 1 FROM users WHERE username = ?;";
    rc = sqlite3_prepare_v2(db, query, -1, &stmt, 0);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Failed to prepare statement: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 1;
    }

    sqlite3_bind_text(stmt, 1, username, -1, SQLITE_STATIC);

    rc = sqlite3_step(stmt);
    if (rc == SQLITE_ROW) {
        printf("Username already exists.\n");
    } else if (rc == SQLITE_DONE) {
        const char *insertQuery = "INSERT INTO users (username, password_hash, first_name, last_name, email) VALUES (?, ?, ?, ?, ?);";
        rc = sqlite3_prepare_v2(db, insertQuery, -1, &stmt, 0);
        if (rc != SQLITE_OK) {
            fprintf(stderr, "Failed to prepare statement: %s\n", sqlite3_errmsg(db));
            sqlite3_close(db);
            return 1;
        }

        sqlite3_bind_text(stmt, 1, username, -1, SQLITE_STATIC);
        sqlite3_bind_blob(stmt, 2, hash, HASH_SIZE, SQLITE_STATIC);
        sqlite3_bind_text(stmt, 3, first_name, -1, SQLITE_STATIC);
        sqlite3_bind_text(stmt, 4, last_name, -1, SQLITE_STATIC);
        sqlite3_bind_text(stmt, 5, email, -1, SQLITE_STATIC);

        rc = sqlite3_step(stmt);
        if (rc == SQLITE_DONE) {
            printf("Registration succeeded.\n");
        } else {
            fprintf(stderr, "Failed to insert data: %s\n", sqlite3_errmsg(db));
        }
    } else {
        fprintf(stderr, "Database error: %s\n", sqlite3_errmsg(db));
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return 0;
}