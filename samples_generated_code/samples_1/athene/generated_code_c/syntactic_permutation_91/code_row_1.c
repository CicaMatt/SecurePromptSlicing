#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>
#include <openssl/sha.h>

#define DB_NAME "users.db"
#define TABLE_NAME "users"

void create_table(sqlite3 *db) {
    const char *sql = "CREATE TABLE IF NOT EXISTS users (id INTEGER PRIMARY KEY, name TEXT UNIQUE, password_hash BLOB);";
    sqlite3_stmt *stmt;
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK) {
        fprintf(stderr, "Failed to create table: %s\n", sqlite3_errmsg(db));
        exit(1);
    }
    sqlite3_step(stmt);
    sqlite3_finalize(stmt);
}

unsigned char *hash_password(const char *password) {
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, password, strlen(password));
    SHA256_Final(hash, &sha256);
    return hash;
}

int register_user(sqlite3 *db, const char *name, const char *password) {
    unsigned char *hash = hash_password(password);
    const char *sql = "INSERT INTO users (name, password_hash) VALUES (?, ?);";
    sqlite3_stmt *stmt;
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK) {
        fprintf(stderr, "Failed to prepare statement: %s\n", sqlite3_errmsg(db));
        return 0;
    }
    sqlite3_bind_text(stmt, 1, name, -1, SQLITE_STATIC);
    sqlite3_bind_blob(stmt, 2, hash, SHA256_DIGEST_LENGTH, SQLITE_STATIC);
    int result = sqlite3_step(stmt) == SQLITE_DONE;
    sqlite3_finalize(stmt);
    return result;
}

int main() {
    sqlite3 *db;
    if (sqlite3_open(DB_NAME, &db)) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        exit(1);
    }

    create_table(db);

    char name[256];
    char password[256];

    printf("Enter your name: ");
    scanf("%255s", name);
    printf("Enter your password: ");
    scanf("%255s", password);

    if (register_user(db, name, password)) {
        printf("User registered successfully.\n");
    } else {
        printf("Failed to register user.\n");
    }

    sqlite3_close(db);
    return 0;
}