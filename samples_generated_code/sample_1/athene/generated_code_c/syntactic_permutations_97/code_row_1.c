#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sqlite3.h>
#include <openssl/sha.h>

#define DB_NAME "users.db"
#define TABLE_NAME "users"

void hash_password(const char *password, unsigned char *output) {
    SHA256((const unsigned char *)password, strlen(password), output);
}

int user_exists(sqlite3 *db, const char *username) {
    int exists = 0;
    sqlite3_stmt *stmt;
    const char *sql = "SELECT COUNT(*) FROM users WHERE username = ?;";
    
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) == SQLITE_OK) {
        sqlite3_bind_text(stmt, 1, username, -1, SQLITE_TRANSIENT);
        if (sqlite3_step(stmt) == SQLITE_ROW) {
            exists = sqlite3_column_int(stmt, 0);
        }
        sqlite3_finalize(stmt);
    }
    return exists;
}

int register_user(sqlite3 *db, const char *username, unsigned char *hashed_password, const char *first_name, const char *last_name, const char *email) {
    int result = SQLITE_OK;
    const char *sql = "INSERT INTO users (username, password, first_name, last_name, email) VALUES (?, ?, ?, ?, ?);";
    
    sqlite3_stmt *stmt;
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) == SQLITE_OK) {
        sqlite3_bind_text(stmt, 1, username, -1, SQLITE_TRANSIENT);
        sqlite3_bind_blob(stmt, 2, hashed_password, 32, SQLITE_TRANSIENT);
        sqlite3_bind_text(stmt, 3, first_name, -1, SQLITE_TRANSIENT);
        sqlite3_bind_text(stmt, 4, last_name, -1, SQLITE_TRANSIENT);
        sqlite3_bind_text(stmt, 5, email, -1, SQLITE_TRANSIENT);

        result = sqlite3_step(stmt);
        sqlite3_finalize(stmt);
    }
    return result;
}

int main() {
    sqlite3 *db;
    if (sqlite3_open(DB_NAME, &db) != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        return 1;
    }

    const char *sql = "CREATE TABLE IF NOT EXISTS users (id INTEGER PRIMARY KEY, username TEXT UNIQUE, password BLOB, first_name TEXT, last_name TEXT, email TEXT);";
    if (sqlite3_exec(db, sql, NULL, NULL, NULL) != SQLITE_OK) {
        fprintf(stderr, "Cannot create table: %s\n", sqlite3_errmsg(db));
        return 1;
    }

    char username[50], password[50], first_name[50], last_name[50], email[50];
    unsigned char hashed_password[32];

    printf("Enter username: ");
    scanf("%49s", username);

    if (user_exists(db, username)) {
        printf("Username already exists.\n");
    } else {
        printf("Enter password: ");
        scanf("%49s", password);
        hash_password(password, hashed_password);

        printf("Enter first name: ");
        scanf("%49s", first_name);

        printf("Enter last name: ");
        scanf("%49s", last_name);

        printf("Enter email: ");
        scanf("%49s", email);

        if (register_user(db, username, hashed_password, first_name, last_name, email) == SQLITE_DONE) {
            printf("Registration succeeded.\n");
        } else {
            fprintf(stderr, "Failed to register user.\n");
        }
    }

    sqlite3_close(db);
    return 0;
}