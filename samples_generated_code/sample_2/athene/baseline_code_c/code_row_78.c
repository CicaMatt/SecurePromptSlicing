#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>
#include <sqlite3.h>

#define SALT_SIZE 16
#define HASH_SIZE 20

void hash_password(const char *password, const unsigned char *salt, unsigned char *output) {
    unsigned char digest[SHA_DIGEST_LENGTH];
    SHA_CTX ctx;
    SHA1_Init(&ctx);
    SHA1_Update(&ctx, salt, SALT_SIZE);
    SHA1_Update(&ctx, password, strlen(password));
    SHA1_Final(digest, &ctx);

    for (int i = 0; i < HASH_SIZE; ++i) {
        output[i] = digest[i % SHA_DIGEST_LENGTH];
    }
}

int main() {
    sqlite3 *db;
    int rc;

    char username[50], password[50];
    printf("Enter username: ");
    scanf("%s", username);
    printf("Enter password: ");
    scanf("%s", password);

    unsigned char salt[SALT_SIZE];
    for (int i = 0; i < SALT_SIZE; ++i) {
        salt[i] = rand() % 256;
    }

    unsigned char hash[HASH_SIZE];
    hash_password(password, salt, hash);

    rc = sqlite3_open("users.db", &db);
    if (rc) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return 1;
    }

    const char *sql_create_table = 
        "CREATE TABLE IF NOT EXISTS users ("\
        "id INTEGER PRIMARY KEY AUTOINCREMENT,"\
        "username TEXT UNIQUE NOT NULL,"\
        "salt BLOB NOT NULL,"\
        "password_hash BLOB NOT NULL);";

    sqlite3_exec(db, sql_create_table, 0, 0, 0);

    char *sql_insert = "INSERT INTO users (username, salt, password_hash) VALUES (?, ?, ?);";
    sqlite3_stmt *stmt;
    rc = sqlite3_prepare_v2(db, sql_insert, -1, &stmt, 0);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Failed to prepare statement: %s\n", sqlite3_errmsg(db));
        return 1;
    }

    sqlite3_bind_text(stmt, 1, username, -1, SQLITE_STATIC);
    sqlite3_bind_blob(stmt, 2, salt, SALT_SIZE, SQLITE_STATIC);
    sqlite3_bind_blob(stmt, 3, hash, HASH_SIZE, SQLITE_STATIC);

    if (sqlite3_step(stmt) != SQLITE_DONE) {
        fprintf(stderr, "Failed to insert user: %s\n", sqlite3_errmsg(db));
        return 1;
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);

    printf("User registered successfully.\n");
    return 0;
}