#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>
#include <sqlite3.h>

#define DB_NAME "users.db"
#define SALT_LENGTH 16

void generate_salt(char *salt, size_t salt_length) {
    for (size_t i = 0; i < salt_length; ++i) {
        salt[i] = 'A' + rand() % ('Z' - 'A');
    }
}

void hash_password(const char *password, const char *salt, unsigned char *digest) {
    SHA256_CTX sha_ctx;
    SHA256_Init(&sha_ctx);
    SHA256_Update(&sha_ctx, salt, SALT_LENGTH);
    SHA256_Update(&sha_ctx, password, strlen(password));
    SHA256_Final(digest, &sha_ctx);
}

void store_user(const char *username, const unsigned char *hashed_password_with_salt) {
    sqlite3 *db;
    if (sqlite3_open(DB_NAME, &db)) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        exit(1);
    }

    char sql[256];
    snprintf(sql, sizeof(sql), "INSERT INTO users (username, password) VALUES ('%s', '%.*s');",
             username, SHA256_DIGEST_LENGTH + SALT_LENGTH, hashed_password_with_salt);

    if (sqlite3_exec(db, sql, 0, 0, 0)) {
        fprintf(stderr, "SQL error: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        exit(1);
    }

    sqlite3_close(db);
}

int main() {
    char username[50], password[50];
    printf("Enter username: ");
    scanf("%49s", username);
    printf("Enter password: ");
    scanf("%49s", password);

    char salt[SALT_LENGTH + 1];
    generate_salt(salt, SALT_LENGTH);
    salt[SALT_LENGTH] = '\0';

    unsigned char hashed_password_with_salt[SHA256_DIGEST_LENGTH + SALT_LENGTH];
    memcpy(hashed_password_with_salt, salt, SALT_LENGTH);
    hash_password(password, salt, hashed_password_with_salt + SALT_LENGTH);

    store_user(username, hashed_password_with_salt);

    printf("User registered successfully!\n");

    return 0;
}