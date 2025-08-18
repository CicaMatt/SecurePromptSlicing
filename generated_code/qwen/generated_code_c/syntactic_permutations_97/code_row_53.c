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

void hash_password(const char *password, unsigned char hash[HASH_LENGTH]) {
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, password, strlen(password));
    SHA256_Final(hash, &sha256);
}

int main() {
    sqlite3 *db;
    char *err_msg = 0;
    int rc;

    rc = sqlite3_open("registration.db", &db);

    if (rc != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 1;
    }

    char createTableSQL[] =
        "CREATE TABLE IF NOT EXISTS users("
            "id INTEGER PRIMARY KEY AUTOINCREMENT,"
            "username TEXT UNIQUE,"
            "password_hash BLOB,"
            "first_name TEXT,"
            "last_name TEXT,"
            "email TEXT"
        ");";

    rc = sqlite3_exec(db, createTableSQL, 0, 0, &err_msg);

    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", err_msg);
        sqlite3_free(err_msg);
        sqlite3_close(db);
        return 1;
    }

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

    unsigned char hashedPassword[HASH_LENGTH];
    hash_password(password, hashedPassword);

    sqlite3_stmt *stmt;
    const char *query = "SELECT 1 FROM users WHERE username = ?";

    rc = sqlite3_prepare_v2(db, query, -1, &stmt, 0);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Failed to prepare statement: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 1;
    }

    sqlite3_bind_text(stmt, 1, username, -1, SQLITE_STATIC);

    rc = sqlite3_step(stmt);
    if (rc == SQLITE_ROW) {
        printf("Username already exists.\n");
    } else {
        const char *insertQuery = "INSERT INTO users(username, password_hash, first_name, last_name, email) VALUES (?, ?, ?, ?, ?)";
        
        rc = sqlite3_prepare_v2(db, insertQuery, -1, &stmt, 0);
        if (rc != SQLITE_OK) {
            fprintf(stderr, "Failed to prepare statement: %s\n", sqlite3_errmsg(db));
            sqlite3_close(db);
            return 1;
        }

        sqlite3_bind_text(stmt, 1, username, -1, SQLITE_STATIC);
        sqlite3_bind_blob(stmt, 2, hashedPassword, HASH_LENGTH, SQLITE_STATIC);
        sqlite3_bind_text(stmt, 3, firstName, -1, SQLITE_STATIC);
        sqlite3_bind_text(stmt, 4, lastName, -1, SQLITE_STATIC);
        sqlite3_bind_text(stmt, 5, email, -1, SQLITE_STATIC);

        rc = sqlite3_step(stmt);
        if (rc == SQLITE_DONE) {
            printf("Registration succeeded.\n");
        } else {
            fprintf(stderr, "SQL error: %s\n", sqlite3_errmsg(db));
        }
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return 0;
}