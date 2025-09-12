#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>
#include <openssl/sha.h>

#define DATABASE "users.db"
#define TABLE_CREATE "CREATE TABLE IF NOT EXISTS users (id INTEGER PRIMARY KEY, username TEXT UNIQUE, password_hash BLOB);"
#define INSERT_USER "INSERT INTO users (username, password_hash) VALUES (?, ?);"

void hash_password(const char *password, unsigned char *output) {
    SHA256((const unsigned char *)password, strlen(password), output);
}

int register_user(sqlite3 *db, const char *username, const char *password) {
    sqlite3_stmt *stmt;
    unsigned char password_hash[SHA256_DIGEST_LENGTH];
    
    hash_password(password, password_hash);

    if (sqlite3_prepare_v2(db, INSERT_USER, -1, &stmt, 0) != SQLITE_OK) {
        return -1;
    }

    sqlite3_bind_text(stmt, 1, username, -1, SQLITE_STATIC);
    sqlite3_bind_blob(stmt, 2, password_hash, SHA256_DIGEST_LENGTH, SQLITE_STATIC);

    int result = sqlite3_step(stmt);
    sqlite3_finalize(stmt);

    if (result != SQLITE_DONE) {
        return -1;
    }

    return 0;
}

int main() {
    sqlite3 *db;
    char username[100];
    char password[100];

    printf("Enter username: ");
    scanf("%99s", username);
    printf("Enter password: ");
    scanf("%99s", password);

    if (sqlite3_open(DATABASE, &db) != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        return 1;
    }

    if (sqlite3_exec(db, TABLE_CREATE, NULL, NULL, NULL) != SQLITE_OK) {
        fprintf(stderr, "Cannot create table: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 1;
    }

    if (register_user(db, username, password) == -1) {
        fprintf(stderr, "Failed to register user: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 1;
    }

    printf("User registered successfully.\n");
    sqlite3_close(db);
    return 0;
}