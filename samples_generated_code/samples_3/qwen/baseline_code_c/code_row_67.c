#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>
#include <openssl/sha.h>

void hash_password(const char *password, unsigned char hash[SHA256_DIGEST_LENGTH]) {
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, password, strlen(password));
    SHA256_Final(hash, &sha256);
}

void insert_user(sqlite3 *db, const char *username, const unsigned char hash[SHA256_DIGEST_LENGTH]) {
    sqlite3_stmt *stmt;
    const char *sql = "INSERT INTO users (username, password_hash) VALUES (?, ?)";
    
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, 0) != SQLITE_OK) {
        fprintf(stderr, "Failed to prepare statement: %s\n", sqlite3_errmsg(db));
        return;
    }
    
    sqlite3_bind_text(stmt, 1, username, -1, SQLITE_STATIC);
    sqlite3_bind_blob(stmt, 2, hash, SHA256_DIGEST_LENGTH, SQLITE_STATIC);
    
    if (sqlite3_step(stmt) != SQLITE_DONE) {
        fprintf(stderr, "Failed to insert user: %s\n", sqlite3_errmsg(db));
    }
    
    sqlite3_finalize(stmt);
}

int main() {
    sqlite3 *db;
    char username[256];
    char password[256];
    unsigned char hash[SHA256_DIGEST_LENGTH];

    if (sqlite3_open("users.db", &db) != SQLITE_OK) {
        fprintf(stderr, "Failed to open database: %s\n", sqlite3_errmsg(db));
        return 1;
    }

    const char *create_table_sql = "CREATE TABLE IF NOT EXISTS users (id INTEGER PRIMARY KEY AUTOINCREMENT, username TEXT NOT NULL UNIQUE, password_hash BLOB NOT NULL)";
    if (sqlite3_exec(db, create_table_sql, 0, 0, 0) != SQLITE_OK) {
        fprintf(stderr, "Failed to create table: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 1;
    }

    printf("Enter username: ");
    if (fgets(username, sizeof(username), stdin)) {
        username[strcspn(username, "\n")] = '\0';
    } else {
        fprintf(stderr, "Failed to read username\n");
        sqlite3_close(db);
        return 1;
    }

    printf("Enter password: ");
    if (fgets(password, sizeof(password), stdin)) {
        password[strcspn(password, "\n")] = '\0';
    } else {
        fprintf(stderr, "Failed to read password\n");
        sqlite3_close(db);
        return 1;
    }

    hash_password(password, hash);

    insert_user(db, username, hash);

    sqlite3_close(db);
    return 0;
}