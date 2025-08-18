#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sqlite3.h>
#include <openssl/sha.h>

#define DB_NAME "users.db"
#define TABLE_NAME "users"
#define USERNAME_SIZE 50
#define PASSWORD_SIZE 64
#define NAME_SIZE 50
#define EMAIL_SIZE 100

void hash_password(const char *password, unsigned char *hash) {
    SHA256((const unsigned char *)password, strlen(password), hash);
}

int user_exists(sqlite3 *db, const char *username) {
    int exists = 0;
    sqlite3_stmt *stmt;
    char sql[100];
    snprintf(sql, sizeof(sql), "SELECT COUNT(*) FROM %s WHERE username=?", TABLE_NAME);

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) == SQLITE_OK) {
        sqlite3_bind_text(stmt, 1, username, -1, SQLITE_STATIC);
        if (sqlite3_step(stmt) == SQLITE_ROW) {
            exists = sqlite3_column_int(stmt, 0) > 0;
        }
        sqlite3_finalize(stmt);
    }
    return exists;
}

int register_user(sqlite3 *db, const char *username, const char *password_hash, const char *first_name, const char *last_name, const char *email) {
    sqlite3_stmt *stmt;
    char sql[200];
    snprintf(sql, sizeof(sql), "INSERT INTO %s (username, password, first_name, last_name, email) VALUES (?, ?, ?, ?, ?)", TABLE_NAME);

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) == SQLITE_OK) {
        sqlite3_bind_text(stmt, 1, username, -1, SQLITE_STATIC);
        sqlite3_bind_blob(stmt, 2, password_hash, PASSWORD_SIZE, SQLITE_STATIC);
        sqlite3_bind_text(stmt, 3, first_name, -1, SQLITE_STATIC);
        sqlite3_bind_text(stmt, 4, last_name, -1, SQLITE_STATIC);
        sqlite3_bind_text(stmt, 5, email, -1, SQLITE_STATIC);

        if (sqlite3_step(stmt) != SQLITE_DONE) {
            return 0;
        }
        sqlite3_finalize(stmt);
    }
    return 1;
}

int main() {
    sqlite3 *db;
    char username[USERNAME_SIZE];
    char password[PASSWORD_SIZE];
    unsigned char password_hash[PASSWORD_SIZE];
    char first_name[NAME_SIZE];
    char last_name[NAME_SIZE];
    char email[EMAIL_SIZE];

    if (sqlite3_open(DB_NAME, &db) != SQLITE_OK) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return 1;
    }

    printf("Enter username: ");
    scanf("%49s", username);
    printf("Enter password: ");
    scanf("%63s", password);
    printf("Enter first name: ");
    scanf("%49s", first_name);
    printf("Enter last name: ");
    scanf("%49s", last_name);
    printf("Enter email: ");
    scanf("%99s", email);

    if (user_exists(db, username)) {
        printf("Username already exists.\n");
    } else {
        hash_password(password, password_hash);
        if (register_user(db, username, password_hash, first_name, last_name, email)) {
            printf("Registration succeeded.\n");
        } else {
            printf("Failed to register user.\n");
        }
    }

    sqlite3_close(db);
    return 0;
}