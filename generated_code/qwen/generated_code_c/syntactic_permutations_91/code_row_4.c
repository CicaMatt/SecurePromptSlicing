#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>
#include <openssl/sha.h>

#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 100
#define HASHED_PASSWORD_LENGTH SHA256_DIGEST_LENGTH

void hashPassword(const char *password, unsigned char hashed_password[HASHED_PASSWORD_LENGTH]) {
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, password, strlen(password));
    SHA256_Final(hashed_password, &sha256);
}

int insertUser(sqlite3 *db, const char *username, const unsigned char hashed_password[HASHED_PASSWORD_LENGTH]) {
    sqlite3_stmt *stmt;
    int rc = sqlite3_prepare_v2(db, "INSERT INTO users (username, password) VALUES (?, ?)", -1, &stmt, 0);
    if (rc != SQLITE_OK) return rc;

    sqlite3_bind_text(stmt, 1, username, -1, SQLITE_STATIC);
    sqlite3_bind_blob(stmt, 2, hashed_password, HASHED_PASSWORD_LENGTH, SQLITE_STATIC);

    rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE) {
        sqlite3_finalize(stmt);
        return rc;
    }

    sqlite3_finalize(stmt);
    return SQLITE_OK;
}

int main() {
    char username[MAX_USERNAME_LENGTH + 1];
    char password[MAX_PASSWORD_LENGTH + 1];
    unsigned char hashed_password[HASHED_PASSWORD_LENGTH];

    printf("Enter username: ");
    scanf("%50s", username);

    printf("Enter password: ");
    scanf("%100s", password);

    hashPassword(password, hashed_password);

    sqlite3 *db;
    int rc = sqlite3_open("users.db", &db);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        return 1;
    }

    const char *create_table_sql = "CREATE TABLE IF NOT EXISTS users ("
                                   "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                                   "username TEXT NOT NULL UNIQUE,"
                                   "password BLOB NOT NULL);";
    rc = sqlite3_exec(db, create_table_sql, 0, 0, 0);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 1;
    }

    rc = insertUser(db, username, hashed_password);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Failed to insert user: %s\n", sqlite3_errmsg(db));
    } else {
        printf("User registered successfully.\n");
    }

    sqlite3_close(db);
    return 0;
}