#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>
#include <sqlite3.h>

#define DB_FILE "users.db"
#define SALT_LENGTH 16

void generate_salt(unsigned char *salt) {
    FILE *urandom = fopen("/dev/urandom", "r");
    fread(salt, sizeof(unsigned char), SALT_LENGTH, urandom);
    fclose(urandom);
}

void hash_password(const char *password, const unsigned char *salt, char *hashed_password) {
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha_ctx;
    SHA256_Init(&sha_ctx);
    SHA256_Update(&sha_ctx, salt, SALT_LENGTH);
    SHA256_Update(&sha_ctx, password, strlen(password));
    SHA256_Final(hash, &sha_ctx);

    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        sprintf(hashed_password + (i * 2), "%02x", hash[i]);
    }
}

int register_user(const char *username, const char *password) {
    sqlite3 *db;
    sqlite3_stmt *stmt;
    int rc;

    if (sqlite3_open(DB_FILE, &db)) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        return 1;
    }

    unsigned char salt[SALT_LENGTH];
    generate_salt(salt);

    char hashed_password[(SHA256_DIGEST_LENGTH * 2) + 1];
    hash_password(password, salt, hashed_password);

    const char *sql = "INSERT INTO users (username, password_hash, salt) VALUES (?, ?, ?)";
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL)) {
        fprintf(stderr, "Failed to prepare statement: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 1;
    }

    sqlite3_bind_text(stmt, 1, username, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, hashed_password, -1, SQLITE_STATIC);
    sqlite3_bind_blob(stmt, 3, salt, SALT_LENGTH, SQLITE_STATIC);

    rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE) {
        fprintf(stderr, "Failed to execute statement: %s\n", sqlite3_errmsg(db));
        sqlite3_finalize(stmt);
        sqlite3_close(db);
        return 1;
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);
    return 0;
}

int main() {
    sqlite3 *db;
    if (sqlite3_open(DB_FILE, &db)) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        return 1;
    }

    const char *create_table_sql = "CREATE TABLE IF NOT EXISTS users (id INTEGER PRIMARY KEY AUTOINCREMENT, username TEXT NOT NULL, password_hash TEXT NOT NULL, salt BLOB NOT NULL)";
    if (sqlite3_exec(db, create_table_sql, NULL, NULL, NULL)) {
        fprintf(stderr, "Failed to create table: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 1;
    }
    sqlite3_close(db);

    char username[50], password[50];
    printf("Enter username: ");
    scanf("%49s", username);
    printf("Enter password: ");
    scanf("%49s", password);

    if (register_user(username, password) == 0) {
        printf("User registered successfully.\n");
    } else {
        printf("Failed to register user.\n");
    }

    return 0;
}