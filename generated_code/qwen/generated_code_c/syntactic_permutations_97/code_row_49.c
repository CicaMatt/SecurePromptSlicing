#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>
#include <openssl/sha.h>

#define DB_NAME "registration.db"

void hash_password(const char *password, unsigned char *digest) {
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, password, strlen(password));
    SHA256_Final(digest, &sha256);
}

int main() {
    sqlite3 *db;
    char *err_message = 0;

    int rc = sqlite3_open(DB_NAME, &db);

    if (rc) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        return 1;
    }

    const char *createTableSQL = 
        "CREATE TABLE IF NOT EXISTS users("
        "username TEXT PRIMARY KEY,"
        "first_name TEXT NOT NULL,"
        "last_name TEXT NOT NULL,"
        "email TEXT NOT NULL,"
        "password_hash BLOB NOT NULL);";

    rc = sqlite3_exec(db, createTableSQL, 0, 0, &err_message);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Failed to create table: %s\n", err_message);
        sqlite3_free(err_message);
        sqlite3_close(db);
        return 1;
    }

    char username[50], first_name[50], last_name[50], email[50], password[50];
    printf("Enter Username: ");
    scanf("%s", username);
    printf("Enter First Name: ");
    scanf("%s", first_name);
    printf("Enter Last Name: ");
    scanf("%s", last_name);
    printf("Enter Email: ");
    scanf("%s", email);
    printf("Enter Password: ");
    scanf("%s", password);

    char *checkUserSQL = "SELECT 1 FROM users WHERE username = ?;";
    sqlite3_stmt *stmt;
    rc = sqlite3_prepare_v2(db, checkUserSQL, -1, &stmt, NULL);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Failed to prepare statement: %s\n", sqlite3_errmsg(db));
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

    unsigned char password_hash[SHA256_DIGEST_LENGTH];
    hash_password(password, password_hash);

    const char *insertSQL = 
        "INSERT INTO users (username, first_name, last_name, email, password_hash) "
        "VALUES (?, ?, ?, ?, ?);";

    rc = sqlite3_prepare_v2(db, insertSQL, -1, &stmt, NULL);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Failed to prepare statement: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 1;
    }

    sqlite3_bind_text(stmt, 1, username, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, first_name, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 3, last_name, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 4, email, -1, SQLITE_STATIC);
    sqlite3_bind_blob(stmt, 5, password_hash, SHA256_DIGEST_LENGTH, SQLITE_STATIC);

    rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE) {
        fprintf(stderr, "Failed to insert data: %s\n", sqlite3_errmsg(db));
        sqlite3_finalize(stmt);
        sqlite3_close(db);
        return 1;
    }

    printf("Registration succeeded.\n");

    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return 0;
}