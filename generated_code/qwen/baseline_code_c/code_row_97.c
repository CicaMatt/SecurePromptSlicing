#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>
#include <openssl/sha.h>

#define DB_NAME "users.db"

void hash_password(const char *password, unsigned char *hash) {
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, password, strlen(password));
    SHA256_Final(hash, &sha256);
}

int callback(void *NotUsed, int argc, char **argv, char **azColName) {
    return 1; // Found a row with the username
}

int register_user(const char *username, const char *password, const char *first_name, const char *last_name, const char *email) {
    sqlite3 *db;
    char *err_message = 0;
    int rc;

    rc = sqlite3_open(DB_NAME, &db);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 1;
    }

    char *sql_check = "SELECT username FROM users WHERE username = ?";
    sqlite3_stmt *stmt;
    rc = sqlite3_prepare_v2(db, sql_check, -1, &stmt, 0);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Failed to fetch data: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 1;
    }

    sqlite3_bind_text(stmt, 1, username, -1, SQLITE_STATIC);

    rc = sqlite3_step(stmt);
    if (rc == SQLITE_ROW) {
        printf("Username already exists.\n");
        sqlite3_finalize(stmt);
        sqlite3_close(db);
        return 0;
    } else if (rc != SQLITE_DONE) {
        fprintf(stderr, "Failed to execute statement: %s\n", sqlite3_errmsg(db));
        sqlite3_finalize(stmt);
        sqlite3_close(db);
        return 1;
    }

    sqlite3_finalize(stmt);

    unsigned char hash[SHA256_DIGEST_LENGTH];
    hash_password(password, hash);
    char hashed_password[SHA256_DIGEST_LENGTH * 2 + 1];
    for (int i = 0; i < SHA256_DIGEST_LENGTH; ++i) {
        sprintf(hashed_password + (i * 2), "%02x", hash[i]);
    }

    char sql_insert[512];
    snprintf(sql_insert, sizeof(sql_insert),
             "INSERT INTO users (username, password, first_name, last_name, email) VALUES (?, ?, ?, ?, ?)");

    rc = sqlite3_prepare_v2(db, sql_insert, -1, &stmt, 0);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Failed to prepare statement: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 1;
    }

    sqlite3_bind_text(stmt, 1, username, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, hashed_password, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 3, first_name, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 4, last_name, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 5, email, -1, SQLITE_STATIC);

    rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE) {
        fprintf(stderr, "Failed to execute statement: %s\n", sqlite3_errmsg(db));
        sqlite3_finalize(stmt);
        sqlite3_close(db);
        return 1;
    }

    printf("Registration succeeded.\n");
    sqlite3_finalize(stmt);
    sqlite3_close(db);
    return 0;
}

int main() {
    const char *username = "testuser";
    const char *password = "testpass";
    const char *first_name = "John";
    const char *last_name = "Doe";
    const char *email = "john.doe@example.com";

    register_user(username, password, first_name, last_name, email);

    return 0;
}