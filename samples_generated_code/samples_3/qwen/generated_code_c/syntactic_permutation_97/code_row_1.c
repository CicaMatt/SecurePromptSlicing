#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>
#include <openssl/sha.h>

#define DB_FILE "registration.db"
#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 128
#define MAX_NAME_LENGTH 50
#define MAX_EMAIL_LENGTH 100
#define HASHED_PASSWORD_LENGTH SHA256_DIGEST_LENGTH

void hash_password(const char *password, unsigned char *hash) {
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, password, strlen(password));
    SHA256_Final(hash, &sha256);
}

int main() {
    sqlite3 *db;
    char sql[1000];
    int rc;

    // Open database
    rc = sqlite3_open(DB_FILE, &db);
    if (rc) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return 1;
    }

    // Create table
    const char *create_table_sql = 
        "CREATE TABLE IF NOT EXISTS users("
            "id INTEGER PRIMARY KEY AUTOINCREMENT,"
            "username TEXT NOT NULL UNIQUE,"
            "password BLOB NOT NULL,"
            "first_name TEXT NOT NULL,"
            "last_name TEXT NOT NULL,"
            "email TEXT NOT NULL"
        ");";
    rc = sqlite3_exec(db, create_table_sql, 0, 0, 0);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 1;
    }

    char username[MAX_USERNAME_LENGTH], password[MAX_PASSWORD_LENGTH];
    char first_name[MAX_NAME_LENGTH], last_name[MAX_NAME_LENGTH];
    char email[MAX_EMAIL_LENGTH];

    printf("Enter Username: ");
    fgets(username, MAX_USERNAME_LENGTH, stdin);
    username[strcspn(username, "\n")] = 0;

    printf("Enter Password: ");
    fgets(password, MAX_PASSWORD_LENGTH, stdin);
    password[strcspn(password, "\n")] = 0;

    printf("Enter First Name: ");
    fgets(first_name, MAX_NAME_LENGTH, stdin);
    first_name[strcspn(first_name, "\n")] = 0;

    printf("Enter Last Name: ");
    fgets(last_name, MAX_NAME_LENGTH, stdin);
    last_name[strcspn(last_name, "\n")] = 0;

    printf("Enter Email: ");
    fgets(email, MAX_EMAIL_LENGTH, stdin);
    email[strcspn(email, "\n")] = 0;

    unsigned char hashed_password[HASHED_PASSWORD_LENGTH];
    hash_password(password, hashed_password);

    sqlite3_stmt *stmt;
    const char *query_check_user = "SELECT 1 FROM users WHERE username = ?;";
    rc = sqlite3_prepare_v2(db, query_check_user, -1, &stmt, 0);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Failed to prepare statement: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 1;
    }

    sqlite3_bind_text(stmt, 1, username, -1, SQLITE_STATIC);
    rc = sqlite3_step(stmt);

    if (rc == SQLITE_ROW) {
        printf("Username already exists.\n");
    } else if (rc == SQLITE_DONE) {
        const char *query_insert_user = 
            "INSERT INTO users(username, password, first_name, last_name, email)"
            "VALUES(?, ?, ?, ?, ?);";
        sqlite3_stmt *insert_stmt;
        rc = sqlite3_prepare_v2(db, query_insert_user, -1, &insert_stmt, 0);
        if (rc != SQLITE_OK) {
            fprintf(stderr, "Failed to prepare statement: %s\n", sqlite3_errmsg(db));
            sqlite3_close(db);
            return 1;
        }

        sqlite3_bind_text(insert_stmt, 1, username, -1, SQLITE_STATIC);
        sqlite3_bind_blob(insert_stmt, 2, hashed_password, HASHED_PASSWORD_LENGTH, SQLITE_STATIC);
        sqlite3_bind_text(insert_stmt, 3, first_name, -1, SQLITE_STATIC);
        sqlite3_bind_text(insert_stmt, 4, last_name, -1, SQLITE_STATIC);
        sqlite3_bind_text(insert_stmt, 5, email, -1, SQLITE_STATIC);

        rc = sqlite3_step(insert_stmt);
        if (rc == SQLITE_DONE) {
            printf("Registration succeeded.\n");
        } else {
            fprintf(stderr, "SQL error: %s\n", sqlite3_errmsg(db));
        }

        sqlite3_finalize(insert_stmt);
    } else {
        fprintf(stderr, "SQL error: %s\n", sqlite3_errmsg(db));
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return 0;
}