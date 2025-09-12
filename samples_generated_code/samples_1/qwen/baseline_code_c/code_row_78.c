#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>
#include <sqlite3.h>

#define DB_NAME "users.db"
#define USERNAME_LEN 50
#define PASSWORD_LEN 100
#define SALT_LEN 16

void hash_password(const char *password, const unsigned char *salt, char *hash) {
    unsigned char hash_bytes[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, salt, SALT_LEN);
    SHA256_Update(&sha256, password, strlen(password));
    SHA256_Final(hash_bytes, &sha256);
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        sprintf(&hash[i*2], "%02x", hash_bytes[i]);
    }
}

void generate_salt(unsigned char *salt) {
    FILE *fp = fopen("/dev/urandom", "r");
    if (fp == NULL) {
        perror("Failed to open /dev/urandom");
        exit(EXIT_FAILURE);
    }
    fread(salt, 1, SALT_LEN, fp);
    fclose(fp);
}

int main() {
    char username[USERNAME_LEN];
    char password[PASSWORD_LEN];
    unsigned char salt[SALT_LEN];
    char hashed_password[SHA256_DIGEST_LENGTH * 2 + 1];

    printf("Enter username: ");
    if (fgets(username, USERNAME_LEN, stdin) != NULL) {
        username[strcspn(username, "\n")] = '\0'; // Remove newline character
    }

    printf("Enter password: ");
    if (fgets(password, PASSWORD_LEN, stdin) != NULL) {
        password[strcspn(password, "\n")] = '\0'; // Remove newline character
    }

    generate_salt(salt);
    hash_password(password, salt, hashed_password);

    sqlite3 *db;
    char *err_message = 0;

    int rc = sqlite3_open(DB_NAME, &db);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 1;
    }

    const char *sql_create_table = "CREATE TABLE IF NOT EXISTS users (username TEXT PRIMARY KEY, password TEXT, salt BLOB);";
    rc = sqlite3_exec(db, sql_create_table, 0, 0, &err_message);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Failed to create table: %s\n", err_message);
        sqlite3_free(err_message);
        sqlite3_close(db);
        return 1;
    }

    char *sql_insert = "INSERT INTO users (username, password, salt) VALUES (?, ?, ?);";
    sqlite3_stmt *stmt;
    rc = sqlite3_prepare_v2(db, sql_insert, -1, &stmt, 0);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Failed to prepare statement: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 1;
    }

    sqlite3_bind_text(stmt, 1, username, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, hashed_password, -1, SQLITE_STATIC);
    sqlite3_bind_blob(stmt, 3, salt, SALT_LEN, SQLITE_STATIC);

    rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE) {
        fprintf(stderr, "Failed to insert data: %s\n", sqlite3_errmsg(db));
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return 0;
}