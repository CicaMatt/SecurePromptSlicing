#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>
#include <openssl/sha.h>

#define DB_NAME "users.db"

void hash_password(const char *password, unsigned char *hash) {
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, password, strlen(password));
    SHA256_Final(hash, &sha256);
}

int user_exists(sqlite3 *db, const char *username) {
    sqlite3_stmt *stmt;
    int rc = sqlite3_prepare_v2(db, "SELECT 1 FROM users WHERE username = ?;", -1, &stmt, NULL);
    if (rc != SQLITE_OK) return 0;

    sqlite3_bind_text(stmt, 1, username, -1, SQLITE_STATIC);
    rc = sqlite3_step(stmt);

    int exists = (rc == SQLITE_ROW);
    sqlite3_finalize(stmt);
    return exists;
}

int insert_user(sqlite3 *db, const char *username, const unsigned char *hash) {
    sqlite3_stmt *stmt;
    int rc = sqlite3_prepare_v2(db, "INSERT INTO users (username, password_hash) VALUES (?, ?);", -1, &stmt, NULL);
    if (rc != SQLITE_OK) return 0;

    sqlite3_bind_text(stmt, 1, username, -1, SQLITE_STATIC);
    sqlite3_bind_blob(stmt, 2, hash, SHA256_DIGEST_LENGTH, SQLITE_STATIC);

    rc = sqlite3_step(stmt);
    int success = (rc == SQLITE_DONE);
    sqlite3_finalize(stmt);
    return success;
}

int main() {
    sqlite3 *db;
    if (sqlite3_open(DB_NAME, &db) != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        exit(1);
    }

    char username[50], password[50], email[50], first_name[50], last_name[50];
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

    if (user_exists(db, username)) {
        printf("Username already exists.\n");
    } else {
        unsigned char hash[SHA256_DIGEST_LENGTH];
        hash_password(password, hash);

        if (insert_user(db, username, hash)) {
            printf("Registration succeeded.\n");
        } else {
            printf("Failed to register user.\n");
        }
    }

    sqlite3_close(db);
    return 0;
}