#include <stdio.h>
#include <string.h>
#include <sqlite3.h>
#include <openssl/sha.h>

#define DB_NAME "users.db"
#define TABLE_NAME "users"
#define USERNAME_MAX 50
#define PASSWORD_MAX 50
#define NAME_MAX 50
#define EMAIL_MAX 100

void hash_password(const char *password, unsigned char *output) {
    SHA256((const unsigned char *)password, strlen(password), output);
}

int check_username_exists(sqlite3 *db, const char *username) {
    int exists = 0;
    sqlite3_stmt *stmt;
    const char *sql = "SELECT COUNT(*) FROM users WHERE username=?";

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) == SQLITE_OK) {
        sqlite3_bind_text(stmt, 1, username, -1, SQLITE_STATIC);
        if (sqlite3_step(stmt) == SQLITE_ROW) {
            exists = sqlite3_column_int(stmt, 0);
        }
    }
    sqlite3_finalize(stmt);
    return exists;
}

int register_user(sqlite3 *db, const char *username, const unsigned char *hashed_password, const char *first_name, const char *last_name, const char *email) {
    int result = SQLITE_ERROR;
    sqlite3_stmt *stmt;
    const char *sql = "INSERT INTO users (username, password, first_name, last_name, email) VALUES (?, ?, ?, ?, ?)";

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) == SQLITE_OK) {
        sqlite3_bind_text(stmt, 1, username, -1, SQLITE_STATIC);
        sqlite3_bind_blob(stmt, 2, hashed_password, SHA256_DIGEST_LENGTH, SQLITE_STATIC);
        sqlite3_bind_text(stmt, 3, first_name, -1, SQLITE_STATIC);
        sqlite3_bind_text(stmt, 4, last_name, -1, SQLITE_STATIC);
        sqlite3_bind_text(stmt, 5, email, -1, SQLITE_STATIC);

        result = sqlite3_step(stmt);
    }
    sqlite3_finalize(stmt);
    return result == SQLITE_DONE;
}

int main() {
    sqlite3 *db;
    char username[USERNAME_MAX];
    char password[PASSWORD_MAX];
    char first_name[NAME_MAX];
    char last_name[NAME_MAX];
    char email[EMAIL_MAX];
    unsigned char hashed_password[SHA256_DIGEST_LENGTH];

    printf("Enter username: ");
    scanf("%49s", username);
    printf("Enter password: ");
    scanf("%49s", password);
    printf("Enter first name: ");
    scanf("%49s", first_name);
    printf("Enter last name: ");
    scanf("%49s", last_name);
    printf("Enter email: ");
    scanf("%99s", email);

    hash_password(password, hashed_password);

    if (sqlite3_open(DB_NAME, &db) == SQLITE_OK) {
        sqlite3_exec(db, "CREATE TABLE IF NOT EXISTS users (id INTEGER PRIMARY KEY, username TEXT UNIQUE, password BLOB, first_name TEXT, last_name TEXT, email TEXT)", NULL, NULL, NULL);

        if (check_username_exists(db, username)) {
            printf("Username already exists.\n");
        } else {
            if (register_user(db, username, hashed_password, first_name, last_name, email)) {
                printf("Registration succeeded.\n");
            } else {
                printf("Registration failed.\n");
            }
        }
        sqlite3_close(db);
    } else {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
    }

    return 0;
}