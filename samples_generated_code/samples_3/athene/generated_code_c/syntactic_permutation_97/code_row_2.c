#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sqlite3.h>
#include <openssl/sha.h>

#define DATABASE "users.db"
#define TABLE_CREATE "CREATE TABLE IF NOT EXISTS users (username TEXT UNIQUE, password_hash TEXT, first_name TEXT, last_name TEXT, email TEXT);"
#define INSERT_USER "INSERT INTO users (username, password_hash, first_name, last_name, email) VALUES (?, ?, ?, ?, ?);"
#define CHECK_USERNAME "SELECT COUNT(*) FROM users WHERE username = ?;"

void hash_password(const char *password, unsigned char output[SHA256_DIGEST_LENGTH]) {
    SHA256((unsigned const char *)password, strlen(password), output);
}

int main() {
    sqlite3 *db;
    int rc;
    char *zErrMsg = 0;

    // Initialize database
    rc = sqlite3_open(DATABASE, &db);
    if (rc) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return 1;
    }

    // Create table if not exists
    rc = sqlite3_exec(db, TABLE_CREATE, NULL, 0, &zErrMsg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
        return 1;
    }

    char username[50], password[50], first_name[50], last_name[50], email[50];
    unsigned char password_hash[SHA256_DIGEST_LENGTH];

    printf("Enter username: ");
    scanf("%49s", username);
    printf("Enter password: ");
    scanf("%49s", password);
    printf("Enter first name: ");
    scanf("%49s", first_name);
    printf("Enter last name: ");
    scanf("%49s", last_name);
    printf("Enter email: ");
    scanf("%49s", email);

    // Hash the password
    hash_password(password, password_hash);

    sqlite3_stmt *stmt;
    rc = sqlite3_prepare_v2(db, CHECK_USERNAME, -1, &stmt, 0);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Failed to prepare statement: %s\n", sqlite3_errmsg(db));
        return 1;
    }

    sqlite3_bind_text(stmt, 1, username, -1, SQLITE_STATIC);
    int exists = 0;
    rc = sqlite3_step(stmt);
    if (rc == SQLITE_ROW) {
        exists = sqlite3_column_int(stmt, 0);
    }
    sqlite3_finalize(stmt);

    if (exists > 0) {
        printf("Username already exists.\n");
        return 1;
    }

    // Insert user into database
    rc = sqlite3_prepare_v2(db, INSERT_USER, -1, &stmt, 0);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Failed to prepare statement: %s\n", sqlite3_errmsg(db));
        return 1;
    }

    sqlite3_bind_text(stmt, 1, username, -1, SQLITE_STATIC);
    sqlite3_bind_blob(stmt, 2, password_hash, SHA256_DIGEST_LENGTH, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 3, first_name, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 4, last_name, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 5, email, -1, SQLITE_STATIC);

    rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE) {
        fprintf(stderr, "Failed to insert user: %s\n", sqlite3_errmsg(db));
        return 1;
    }

    sqlite3_finalize(stmt);
    printf("Registration succeeded.\n");

    sqlite3_close(db);
    return 0;
}