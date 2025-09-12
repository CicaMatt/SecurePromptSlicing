#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>
#include <sqlite3.h>

#define DB_NAME "users.db"
#define TABLE_NAME "users"
#define HASH_LENGTH 64

void create_table(sqlite3 *db) {
    const char *sql = "CREATE TABLE IF NOT EXISTS users (id INTEGER PRIMARY KEY, username TEXT UNIQUE, password_hash TEXT);";
    sqlite3_stmt *stmt;
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK) {
        fprintf(stderr, "Error creating table: %s\n", sqlite3_errmsg(db));
        exit(1);
    }
    sqlite3_step(stmt);
    sqlite3_finalize(stmt);
}

char *hash_password(const char *password) {
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, password, strlen(password));
    SHA256_Final(hash, &sha256);

    char *hash_str = malloc(HASH_LENGTH + 1);
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        sprintf(hash_str + (i * 2), "%02x", hash[i]);
    }
    hash_str[HASH_LENGTH] = '\0';
    return hash_str;
}

void register_user(sqlite3 *db, const char *username, const char *password) {
    char *hash = hash_password(password);
    const char *sql = "INSERT INTO users (username, password_hash) VALUES (?, ?);";
    sqlite3_stmt *stmt;

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK) {
        fprintf(stderr, "Error preparing statement: %s\n", sqlite3_errmsg(db));
        exit(1);
    }

    sqlite3_bind_text(stmt, 1, username, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, hash, -1, SQLITE_STATIC);

    if (sqlite3_step(stmt) != SQLITE_DONE) {
        fprintf(stderr, "Error inserting data: %s\n", sqlite3_errmsg(db));
        exit(1);
    }

    sqlite3_finalize(stmt);
    free(hash);
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <username> <password>\n", argv[0]);
        return 1;
    }

    sqlite3 *db;
    int rc = sqlite3_open(DB_NAME, &db);
    if (rc) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return 1;
    }

    create_table(db);
    register_user(db, argv[1], argv[2]);

    sqlite3_close(db);
    return 0;
}