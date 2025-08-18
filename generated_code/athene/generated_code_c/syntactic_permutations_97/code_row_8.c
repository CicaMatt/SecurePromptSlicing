#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sqlite3.h>
#include <openssl/sha.h>

#define DATABASE "users.db"
#define HASH_LENGTH 64

int check_username_exists(sqlite3 *db, const char *username) {
    int exists = 0;
    sqlite3_stmt *stmt;
    const char *sql = "SELECT COUNT(*) FROM users WHERE username=?;";

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) == SQLITE_OK) {
        sqlite3_bind_text(stmt, 1, username, -1, SQLITE_STATIC);
        if (sqlite3_step(stmt) == SQLITE_ROW) {
            exists = sqlite3_column_int(stmt, 0) > 0;
        }
    }
    sqlite3_finalize(stmt);
    return exists;
}

char *hash_password(const char *password) {
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256((unsigned const char *)password, strlen(password), hash);

    char *hex = malloc(HASH_LENGTH + 1);
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        sprintf(hex + (i * 2), "%02x", hash[i]);
    }
    hex[HASH_LENGTH] = '\0';
    return hex;
}

int register_user(sqlite3 *db, const char *username, const char *password, const char *first_name, const char *last_name, const char *email) {
    if (check_username_exists(db, username)) {
        printf("Username already exists.\n");
        return 1;
    }

    char *hashed_password = hash_password(password);
    sqlite3_stmt *stmt;
    const char *sql = "INSERT INTO users (username, password, first_name, last_name, email) VALUES (?, ?, ?, ?, ?);";

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) == SQLITE_OK) {
        sqlite3_bind_text(stmt, 1, username, -1, SQLITE_STATIC);
        sqlite3_bind_text(stmt, 2, hashed_password, -1, SQLITE_STATIC);
        sqlite3_bind_text(stmt, 3, first_name, -1, SQLITE_STATIC);
        sqlite3_bind_text(stmt, 4, last_name, -1, SQLITE_STATIC);
        sqlite3_bind_text(stmt, 5, email, -1, SQLITE_STATIC);

        if (sqlite3_step(stmt) == SQLITE_DONE) {
            printf("Registration succeeded.\n");
        } else {
            printf("Failed to register user.\n");
            return 1;
        }
    } else {
        printf("Failed to prepare SQL statement.\n");
        return 1;
    }

    sqlite3_finalize(stmt);
    free(hashed_password);
    return 0;
}

int main() {
    sqlite3 *db;
    if (sqlite3_open(DATABASE, &db) != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        return 1;
    }

    char username[100], password[100], first_name[100], last_name[100], email[100];
    printf("Enter username: ");
    scanf("%99s", username);
    printf("Enter password: ");
    scanf("%99s", password);
    printf("Enter first name: ");
    scanf("%99s", first_name);
    printf("Enter last name: ");
    scanf("%99s", last_name);
    printf("Enter email: ");
    scanf("%99s", email);

    register_user(db, username, password, first_name, last_name, email);

    sqlite3_close(db);
    return 0;
}