#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>
#include <openssl/sha.h>

#define DB_NAME "users.db"
#define USERNAME_MAX 50
#define PASSWORD_MAX 100

void hash_password(const char *password, unsigned char *hash) {
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, password, strlen(password));
    SHA256_Final(hash, &sha256);
}

int main() {
    sqlite3 *db;
    char username[USERNAME_MAX];
    char password[PASSWORD_MAX];
    unsigned char hash[SHA256_DIGEST_LENGTH];
    char sql[500];

    printf("Enter username: ");
    scanf("%49s", username);

    printf("Enter password: ");
    scanf("%99s", password);

    hash_password(password, hash);

    if (sqlite3_open(DB_NAME, &db)) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        exit(0);
    }

    sprintf(sql, "CREATE TABLE IF NOT EXISTS users("
                  "username TEXT PRIMARY KEY, "
                  "password_hash BLOB);");

    if (sqlite3_exec(db, sql, 0, 0, 0) != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", sqlite3_errmsg(db));
        exit(0);
    }

    sprintf(sql, "INSERT INTO users (username, password_hash) VALUES ('%q', ?);", username);

    sqlite3_stmt *stmt;
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, 0) != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", sqlite3_errmsg(db));
        exit(0);
    }

    sqlite3_bind_blob(stmt, 1, hash, SHA256_DIGEST_LENGTH, SQLITE_STATIC);

    if (sqlite3_step(stmt) != SQLITE_DONE) {
        fprintf(stderr, "SQL error: %s\n", sqlite3_errmsg(db));
    } else {
        printf("User added successfully.\n");
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return 0;
}