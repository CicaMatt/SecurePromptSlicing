#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>
#include <openssl/sha.h>

#define DB_NAME "users.db"

void hash_password(const char *password, char *hashed_password) {
    unsigned char digest[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, password, strlen(password));
    SHA256_Final(digest, &sha256);

    for (int i = 0; i < SHA256_DIGEST_LENGTH; ++i) {
        sprintf(&hashed_password[i*2], "%02x", digest[i]);
    }
}

int user_exists(sqlite3 *db, const char *username) {
    sqlite3_stmt *stmt;
    int exists = 0;

    if (sqlite3_prepare_v2(db, "SELECT username FROM users WHERE username = ?", -1, &stmt, NULL) == SQLITE_OK) {
        sqlite3_bind_text(stmt, 1, username, -1, SQLITE_STATIC);
        if (sqlite3_step(stmt) == SQLITE_ROW) {
            exists = 1;
        }
    }

    sqlite3_finalize(stmt);
    return exists;
}

void register_user(sqlite3 *db, const char *username, const char *password, const char *first_name, const char *last_name, const char *email) {
    char hashed_password[SHA256_DIGEST_LENGTH * 2 + 1];
    hash_password(password, hashed_password);

    if (user_exists(db, username)) {
        printf("Username already exists.\n");
        return;
    }

    sqlite3_stmt *stmt;
    if (sqlite3_prepare_v2(db, "INSERT INTO users (username, password, first_name, last_name, email) VALUES (?, ?, ?, ?, ?)", -1, &stmt, NULL) == SQLITE_OK) {
        sqlite3_bind_text(stmt, 1, username, -1, SQLITE_STATIC);
        sqlite3_bind_text(stmt, 2, hashed_password, -1, SQLITE_STATIC);
        sqlite3_bind_text(stmt, 3, first_name, -1, SQLITE_STATIC);
        sqlite3_bind_text(stmt, 4, last_name, -1, SQLITE_STATIC);
        sqlite3_bind_text(stmt, 5, email, -1, SQLITE_STATIC);

        if (sqlite3_step(stmt) == SQLITE_DONE) {
            printf("Registration succeeded.\n");
        } else {
            printf("Failed to register user.\n");
        }
    }

    sqlite3_finalize(stmt);
}

int main() {
    sqlite3 *db;
    int rc = sqlite3_open(DB_NAME, &db);

    if (rc != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        return 1;
    }

    const char *sql = "CREATE TABLE IF NOT EXISTS users("
                      "username TEXT PRIMARY KEY,"
                      "password TEXT NOT NULL,"
                      "first_name TEXT NOT NULL,"
                      "last_name TEXT NOT NULL,"
                      "email TEXT NOT NULL"
                      ");";

    rc = sqlite3_exec(db, sql, 0, 0, 0);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 1;
    }

    char username[50], password[50], first_name[50], last_name[50], email[50];

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

    register_user(db, username, password, first_name, last_name, email);

    sqlite3_close(db);
    return 0;
}