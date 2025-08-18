#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>
#include <sqlite3.h>

#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 100
#define SALT_LENGTH 8

void generate_salt(unsigned char *salt) {
    FILE *fp = fopen("/dev/urandom", "r");
    if (fp == NULL) {
        perror("Failed to open /dev/urandom");
        exit(EXIT_FAILURE);
    }
    fread(salt, sizeof(*salt), SALT_LENGTH, fp);
    fclose(fp);
}

void hash_password_with_salt(const char *password, const unsigned char *salt, unsigned char *hash) {
    SHA512_CTX sha_ctx;
    SHA512_Init(&sha_ctx);
    SHA512_Update(&sha_ctx, password, strlen(password));
    SHA512_Update(&sha_ctx, salt, SALT_LENGTH);
    SHA512_Final(hash, &sha_ctx);
}

void store_user_in_db(const char *username, const unsigned char *salted_hash) {
    sqlite3 *db;
    char *err_message = 0;

    int rc = sqlite3_open("users.db", &db);

    if (rc != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return;
    }

    const char* create_table_sql = "CREATE TABLE IF NOT EXISTS users("
                                   "username TEXT PRIMARY KEY,"
                                   "salted_hash BLOB);";
    rc = sqlite3_exec(db, create_table_sql, 0, 0, &err_message);

    if (rc != SQLITE_OK) {
        fprintf(stderr, "Failed to create table: %s\n", err_message);
        sqlite3_free(err_message);
        sqlite3_close(db);
        return;
    }

    char insert_user_sql[256];
    snprintf(insert_user_sql, sizeof(insert_user_sql),
             "INSERT INTO users (username, salted_hash) VALUES ('%s', ?);",
             username);

    sqlite3_stmt *stmt;
    rc = sqlite3_prepare_v2(db, insert_user_sql, -1, &stmt, 0);

    if (rc != SQLITE_OK) {
        fprintf(stderr, "Failed to prepare statement: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return;
    }

    sqlite3_bind_blob(stmt, 1, salted_hash, SHA512_DIGEST_LENGTH + SALT_LENGTH, SQLITE_STATIC);

    rc = sqlite3_step(stmt);

    if (rc != SQLITE_DONE) {
        fprintf(stderr, "Failed to insert user: %s\n", sqlite3_errmsg(db));
    } else {
        printf("User registered successfully.\n");
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);
}

int main() {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
    unsigned char salt[SALT_LENGTH];
    unsigned char salted_hash[SHA512_DIGEST_LENGTH + SALT_LENGTH];

    printf("Enter username: ");
    scanf("%49s", username);

    printf("Enter password: ");
    scanf("%99s", password);

    generate_salt(salt);
    hash_password_with_salt(password, salt, salted_hash);

    memcpy(salted_hash + SHA512_DIGEST_LENGTH, salt, SALT_LENGTH);

    store_user_in_db(username, salted_hash);

    return 0;
}