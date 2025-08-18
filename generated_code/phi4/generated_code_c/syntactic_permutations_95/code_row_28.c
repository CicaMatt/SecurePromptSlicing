#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "sqlite3.h"
#include <openssl/sha.h>

#define SALT_SIZE 16

void generate_salt(char *salt) {
    const char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    int index;
    for (int i = 0; i < SALT_SIZE - 1; i++) {
        index = rand() % (sizeof(charset) - 1);
        salt[i] = charset[index];
    }
    salt[SALT_SIZE - 1] = '\0';
}

void hash_password(const char *password, const char *salt, unsigned char *digest) {
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, password, strlen(password));
    SHA256_Update(&sha256, salt, SALT_SIZE - 1);
    SHA256_Final(digest, &sha256);
}

void create_table(sqlite3 *db) {
    char *errMsg = NULL;
    const char *sql = "CREATE TABLE IF NOT EXISTS users ("
                      "username TEXT PRIMARY KEY, "
                      "password_hash BLOB, "
                      "salt TEXT);";

    if (sqlite3_exec(db, sql, 0, 0, &errMsg) != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", errMsg);
        sqlite3_free(errMsg);
    }
}

void insert_user(sqlite3 *db, const char *username, unsigned char *digest, const char *salt) {
    char stmt[512];
    snprintf(stmt, sizeof(stmt),
             "INSERT INTO users (username, password_hash, salt) VALUES ('%s', ?, '%s');",
             username);

    sqlite3_stmt *ppStmt;
    if (sqlite3_prepare_v2(db, stmt, -1, &ppStmt, NULL) == SQLITE_OK) {
        sqlite3_bind_blob(ppStmt, 1, digest, SHA256_DIGEST_LENGTH, SQLITE_STATIC);
        if (sqlite3_step(ppStmt) != SQLITE_DONE) {
            fprintf(stderr, "Failed to insert user: %s\n", sqlite3_errmsg(db));
        }
        sqlite3_finalize(ppStmt);
    } else {
        fprintf(stderr, "SQL error: %s\n", sqlite3_errmsg(db));
    }
}

int main() {
    sqlite3 *db;
    if (sqlite3_open("users.db", &db)) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return 1;
    }

    create_table(db);

    char username[50];
    char password[100];

    printf("Enter username: ");
    scanf("%49s", username);
    printf("Enter password: ");
    scanf("%99s", password);

    unsigned char digest[SHA256_DIGEST_LENGTH];
    char salt[SALT_SIZE + 1];

    srand(time(NULL));
    generate_salt(salt);

    hash_password(password, salt, digest);

    insert_user(db, username, digest, salt);

    printf("User registered successfully.\n");

    sqlite3_close(db);
    return 0;
}