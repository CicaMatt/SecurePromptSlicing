#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>
#include <openssl/sha.h>

#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 100
#define MAX_NAME_LENGTH 50
#define MAX_EMAIL_LENGTH 100
#define HASH_LENGTH SHA256_DIGEST_LENGTH

void hashPassword(const char *password, unsigned char *hash) {
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, password, strlen(password));
    SHA256_Final(hash, &sha256);
}

int userExists(sqlite3 *db, const char *username) {
    sqlite3_stmt *stmt;
    int rc = sqlite3_prepare_v2(db, "SELECT 1 FROM users WHERE username = ?;", -1, &stmt, NULL);
    if (rc != SQLITE_OK) return 0;

    sqlite3_bind_text(stmt, 1, username, -1, SQLITE_STATIC);
    rc = sqlite3_step(stmt);

    int exists = (rc == SQLITE_ROW);
    sqlite3_finalize(stmt);
    return exists;
}

void insertUser(sqlite3 *db, const char *username, const unsigned char *hash, const char *firstName, const char *lastName, const char *email) {
    sqlite3_stmt *stmt;
    int rc = sqlite3_prepare_v2(db, "INSERT INTO users (username, password_hash, first_name, last_name, email) VALUES (?, ?, ?, ?, ?);", -1, &stmt, NULL);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Failed to prepare statement: %s\n", sqlite3_errmsg(db));
        return;
    }

    sqlite3_bind_text(stmt, 1, username, -1, SQLITE_STATIC);
    sqlite3_bind_blob(stmt, 2, hash, HASH_LENGTH, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 3, firstName, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 4, lastName, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 5, email, -1, SQLITE_STATIC);

    rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE) {
        fprintf(stderr, "Failed to insert user: %s\n", sqlite3_errmsg(db));
    } else {
        printf("Registration succeeded.\n");
    }

    sqlite3_finalize(stmt);
}

int main() {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
    char firstName[MAX_NAME_LENGTH];
    char lastName[MAX_NAME_LENGTH];
    char email[MAX_EMAIL_LENGTH];

    printf("Enter Username: ");
    scanf("%s", username);

    printf("Enter Password: ");
    scanf("%s", password);

    printf("Enter First Name: ");
    scanf("%s", firstName);

    printf("Enter Last Name: ");
    scanf("%s", lastName);

    printf("Enter Email: ");
    scanf("%s", email);

    sqlite3 *db;
    int rc = sqlite3_open("registration.db", &db);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 1;
    }

    const char *createTableSQL = 
        "CREATE TABLE IF NOT EXISTS users ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "username TEXT NOT NULL UNIQUE,"
        "password_hash BLOB NOT NULL,"
        "first_name TEXT NOT NULL,"
        "last_name TEXT NOT NULL,"
        "email TEXT NOT NULL);";

    rc = sqlite3_exec(db, createTableSQL, 0, 0, 0);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Failed to create table: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 1;
    }

    if (userExists(db, username)) {
        printf("Username already exists.\n");
    } else {
        unsigned char hash[HASH_LENGTH];
        hashPassword(password, hash);
        insertUser(db, username, hash, firstName, lastName, email);
    }

    sqlite3_close(db);
    return 0;
}