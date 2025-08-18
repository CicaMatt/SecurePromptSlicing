#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>
#include <sqlite3.h>

#define SALT_SIZE 16

void generate_salt(unsigned char *salt, size_t salt_size) {
    FILE *urandom = fopen("/dev/urandom", "r");
    if (urandom == NULL) {
        perror("Failed to open /dev/urandom");
        exit(EXIT_FAILURE);
    }
    fread(salt, 1, salt_size, urandom);
    fclose(urandom);
}

void hash_password(const char *password, const unsigned char *salt, size_t salt_size, unsigned char *hash) {
    SHA256_CTX sha_ctx;
    SHA256_Init(&sha_ctx);
    SHA256_Update(&sha_ctx, salt, salt_size);
    SHA256_Update(&sha_ctx, password, strlen(password));
    SHA256_Final(hash, &sha_ctx);
}

void insert_user_into_db(const char *username, const unsigned char *hashed_password, size_t hash_size) {
    sqlite3 *db;
    int rc = sqlite3_open("users.db", &db);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        exit(EXIT_FAILURE);
    }

    const char *sql_create_table = "CREATE TABLE IF NOT EXISTS users (username TEXT PRIMARY KEY, hashed_password BLOB, salt BLOB);";
    rc = sqlite3_exec(db, sql_create_table, 0, 0, 0);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        exit(EXIT_FAILURE);
    }

    unsigned char salt[SALT_SIZE];
    generate_salt(salt, SALT_SIZE);

    unsigned char hashed_password_with_salt[SHA256_DIGEST_LENGTH];
    hash_password(username, salt, SALT_SIZE, hashed_password_with_salt);

    sqlite3_stmt *stmt;
    const char *sql_insert = "INSERT INTO users (username, hashed_password, salt) VALUES (?, ?, ?);";
    rc = sqlite3_prepare_v2(db, sql_insert, -1, &stmt, 0);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        exit(EXIT_FAILURE);
    }

    sqlite3_bind_text(stmt, 1, username, -1, SQLITE_STATIC);
    sqlite3_bind_blob(stmt, 2, hashed_password_with_salt, SHA256_DIGEST_LENGTH, SQLITE_STATIC);
    sqlite3_bind_blob(stmt, 3, salt, SALT_SIZE, SQLITE_STATIC);

    rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE) {
        fprintf(stderr, "SQL error: %s\n", sqlite3_errmsg(db));
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);
}

int main() {
    char username[100];
    char password[100];

    printf("Enter your username: ");
    scanf("%99s", username);

    printf("Enter your password: ");
    scanf("%99s", password);

    unsigned char hashed_password[SHA256_DIGEST_LENGTH];
    insert_user_into_db(username, hashed_password, SHA256_DIGEST_LENGTH);

    return 0;
}