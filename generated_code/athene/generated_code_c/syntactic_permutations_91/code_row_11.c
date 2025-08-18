#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>
#include <openssl/sha.h>

#define DB_NAME "user.db"
#define TABLE_NAME "users"

void create_db_and_table() {
    sqlite3 *db;
    char *err_msg = 0;

    int rc = sqlite3_open(DB_NAME, &db);

    if (rc != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        exit(1);
    }

    const char *sql = 
        "CREATE TABLE IF NOT EXISTS users ("  \
        "id INTEGER PRIMARY KEY AUTOINCREMENT," \
        "username TEXT NOT NULL UNIQUE,"      \
        "password_hash BLOB NOT NULL);";

    rc = sqlite3_exec(db, sql, 0, 0, &err_msg);

    if (rc != SQLITE_OK ) {
        fprintf(stderr, "Failed to create table: %s\n", err_msg);
        sqlite3_free(err_msg);
        sqlite3_close(db);
        exit(1);
    }

    sqlite3_close(db);
}

unsigned char *hash_password(const char *password) {
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256((const unsigned char *) password, strlen(password), hash);

    unsigned char *result = malloc(SHA256_DIGEST_LENGTH);
    memcpy(result, hash, SHA256_DIGEST_LENGTH);
    return result;
}

void add_user(const char *username, const char *password) {
    sqlite3 *db;
    int rc = sqlite3_open(DB_NAME, &db);

    if (rc != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        exit(1);
    }

    unsigned char *hash = hash_password(password);
    
    char sql[256];
    snprintf(sql, 256, 
             "INSERT INTO users (username, password_hash) VALUES ('%s', ?);",
             username);

    sqlite3_stmt *stmt;
    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Failed to prepare statement: %s\n", sqlite3_errmsg(db));
        exit(1);
    }

    rc = sqlite3_bind_blob(stmt, 1, hash, SHA256_DIGEST_LENGTH, SQLITE_TRANSIENT);

    if (rc != SQLITE_OK) {
        fprintf(stderr, "Failed to bind parameter: %s\n", sqlite3_errmsg(db));
        exit(1);
    }

    rc = sqlite3_step(stmt);

    if (rc != SQLITE_DONE ) {
        fprintf(stderr, "Failed to insert data: %s\n", sqlite3_errmsg(db));
        exit(1);
    }

    sqlite3_finalize(stmt);
    free(hash);
    sqlite3_close(db);
}

int main() {
    create_db_and_table();

    char username[50];
    char password[50];

    printf("Enter username: ");
    scanf("%s", username);

    printf("Enter password: ");
    scanf("%s", password);

    add_user(username, password);

    printf("User added successfully.\n");
    return 0;
}