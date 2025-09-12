#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>
#include <openssl/sha.h>

#define DB_NAME "registration.db"
#define MAX_USERNAME_LENGTH 50
#define MAX_NAME_LENGTH 50
#define MAX_EMAIL_LENGTH 100

void hash_password(const char *password, char *hash) {
    unsigned char digest[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, password, strlen(password));
    SHA256_Final(digest, &sha256);

    for(int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        sprintf(&hash[i*2], "%02x", (unsigned int)digest[i]);
    }
}

int check_username_exists(sqlite3 *db, const char *username) {
    sqlite3_stmt *stmt;
    int rc = sqlite3_prepare_v2(db, "SELECT 1 FROM users WHERE username = ?;", -1, &stmt, NULL);
    if (rc != SQLITE_OK) return 0;

    sqlite3_bind_text(stmt, 1, username, -1, SQLITE_STATIC);
    int exists = sqlite3_step(stmt) == SQLITE_ROW;
    sqlite3_finalize(stmt);
    return exists;
}

void register_user(sqlite3 *db, const char *username, const char *first_name, const char *last_name, const char *email, const char *password) {
    if (check_username_exists(db, username)) {
        printf("Username already exists.\n");
        return;
    }

    char hash[SHA256_DIGEST_LENGTH*2 + 1];
    hash_password(password, hash);

    sqlite3_stmt *stmt;
    int rc = sqlite3_prepare_v2(db, "INSERT INTO users (username, first_name, last_name, email, password_hash) VALUES (?, ?, ?, ?, ?);", -1, &stmt, NULL);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Failed to prepare statement: %s\n", sqlite3_errmsg(db));
        return;
    }

    sqlite3_bind_text(stmt, 1, username, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, first_name, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 3, last_name, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 4, email, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 5, hash, -1, SQLITE_STATIC);

    rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE) {
        fprintf(stderr, "Failed to insert user: %s\n", sqlite3_errmsg(db));
    } else {
        printf("Registration succeeded.\n");
    }

    sqlite3_finalize(stmt);
}

int main() {
    sqlite3 *db;
    int rc = sqlite3_open(DB_NAME, &db);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return 1;
    }

    const char *create_table_sql = "CREATE TABLE IF NOT EXISTS users (id INTEGER PRIMARY KEY AUTOINCREMENT, username TEXT NOT NULL UNIQUE, first_name TEXT, last_name TEXT, email TEXT, password_hash TEXT);";
    rc = sqlite3_exec(db, create_table_sql, NULL, NULL, NULL);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Failed to create table: %s\n", sqlite3_errmsg(db));
        return 1;
    }

    char username[MAX_USERNAME_LENGTH], first_name[MAX_NAME_LENGTH], last_name[MAX_NAME_LENGTH], email[MAX_EMAIL_LENGTH], password[50];

    printf("Enter username: ");
    scanf("%49s", username);
    printf("Enter first name: ");
    scanf("%49s", first_name);
    printf("Enter last name: ");
    scanf("%49s", last_name);
    printf("Enter email: ");
    scanf("%99s", email);
    printf("Enter password: ");
    scanf("%49s", password);

    register_user(db, username, first_name, last_name, email, password);

    sqlite3_close(db);
    return 0;
}