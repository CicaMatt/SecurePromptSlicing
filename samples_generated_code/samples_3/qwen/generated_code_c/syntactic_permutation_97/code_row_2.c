#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>
#include <openssl/sha.h>

#define DB_NAME "registration.db"
#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 128
#define MAX_NAME_LENGTH 50
#define MAX_EMAIL_LENGTH 100

void hash_password(const char *password, char *hashed_password) {
    unsigned char digest[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, password, strlen(password));
    SHA256_Final(digest, &sha256);

    for (int i = 0; i < SHA256_DIGEST_LENGTH; ++i) {
        sprintf(&hashed_password[i * 2], "%02x", digest[i]);
    }
}

int check_username_exists(sqlite3 *db, const char *username) {
    sqlite3_stmt *stmt;
    int rc = sqlite3_prepare_v2(db, "SELECT COUNT(*) FROM users WHERE username = ?", -1, &stmt, NULL);
    if (rc != SQLITE_OK) return 0;

    sqlite3_bind_text(stmt, 1, username, -1, SQLITE_STATIC);
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        int count = sqlite3_column_int(stmt, 0);
        sqlite3_finalize(stmt);
        return count > 0;
    }
    sqlite3_finalize(stmt);
    return 0;
}

int register_user(sqlite3 *db, const char *username, const char *password, const char *first_name, const char *last_name, const char *email) {
    if (check_username_exists(db, username)) {
        printf("Username already exists.\n");
        return 1;
    }

    char hashed_password[SHA256_DIGEST_LENGTH * 2 + 1];
    hash_password(password, hashed_password);

    sqlite3_stmt *stmt;
    int rc = sqlite3_prepare_v2(db, "INSERT INTO users (username, password, first_name, last_name, email) VALUES (?, ?, ?, ?, ?)", -1, &stmt, NULL);
    if (rc != SQLITE_OK) return 0;

    sqlite3_bind_text(stmt, 1, username, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, hashed_password, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 3, first_name, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 4, last_name, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 5, email, -1, SQLITE_STATIC);

    rc = sqlite3_step(stmt);
    if (rc == SQLITE_DONE) {
        printf("Registration succeeded.\n");
    } else {
        printf("Error inserting data: %s\n", sqlite3_errmsg(db));
    }

    sqlite3_finalize(stmt);
    return rc == SQLITE_DONE;
}

int main() {
    sqlite3 *db;
    int rc = sqlite3_open(DB_NAME, &db);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 1;
    }

    const char *sql_create_table = "CREATE TABLE IF NOT EXISTS users ("
                                   "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                                   "username TEXT UNIQUE NOT NULL,"
                                   "password TEXT NOT NULL,"
                                   "first_name TEXT NOT NULL,"
                                   "last_name TEXT NOT NULL,"
                                   "email TEXT NOT NULL"
                                   ");";

    rc = sqlite3_exec(db, sql_create_table, 0, 0, 0);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 1;
    }

    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
    char first_name[MAX_NAME_LENGTH];
    char last_name[MAX_NAME_LENGTH];
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

    register_user(db, username, password, first_name, last_name, email);

    sqlite3_close(db);
    return 0;
}