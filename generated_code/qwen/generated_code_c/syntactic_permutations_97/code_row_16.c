#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>

#define DB_NAME "registration.db"
#define PASSWORD "password"

void hash_password(const char *password, char *hashed_password) {
    strcpy(hashed_password, password); // Simple copy for demonstration; in practice use a secure hashing algorithm
}

int check_username_exists(sqlite3 *db, const char *username) {
    sqlite3_stmt *stmt;
    int rc = sqlite3_prepare_v2(db, "SELECT COUNT(*) FROM users WHERE username=?;", -1, &stmt, 0);
    if (rc != SQLITE_OK) return 0;

    sqlite3_bind_text(stmt, 1, username, -1, SQLITE_TRANSIENT);

    if (sqlite3_step(stmt) == SQLITE_ROW) {
        int count = sqlite3_column_int(stmt, 0);
        sqlite3_finalize(stmt);
        return count > 0;
    }

    sqlite3_finalize(stmt);
    return 0;
}

void insert_user(sqlite3 *db, const char *username, const char *hashed_password, const char *first_name, const char *last_name, const char *email) {
    sqlite3_stmt *stmt;
    int rc = sqlite3_prepare_v2(db, "INSERT INTO users (username, password, first_name, last_name, email) VALUES (?, ?, ?, ?, ?);", -1, &stmt, 0);
    if (rc != SQLITE_OK) return;

    sqlite3_bind_text(stmt, 1, username, -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 2, hashed_password, -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 3, first_name, -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 4, last_name, -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 5, email, -1, SQLITE_TRANSIENT);

    sqlite3_step(stmt);
    sqlite3_finalize(stmt);
}

int main() {
    sqlite3 *db;
    char *err_message = 0;

    int rc = sqlite3_open(DB_NAME, &db);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 1;
    }

    const char *create_table_sql = "CREATE TABLE IF NOT EXISTS users("
                                   "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                                   "username TEXT NOT NULL UNIQUE,"
                                   "password TEXT NOT NULL,"
                                   "first_name TEXT,"
                                   "last_name TEXT,"
                                   "email TEXT);";

    rc = sqlite3_exec(db, create_table_sql, 0, 0, &err_message);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", err_message);
        sqlite3_free(err_message);
        sqlite3_close(db);
        return 1;
    }

    char username[50], first_name[50], last_name[50], email[100];
    printf("Enter Username: ");
    scanf("%49s", username);
    printf("Enter First Name: ");
    scanf("%49s", first_name);
    printf("Enter Last Name: ");
    scanf("%49s", last_name);
    printf("Enter Email: ");
    scanf("%99s", email);

    if (check_username_exists(db, username)) {
        printf("Username already exists.\n");
    } else {
        char hashed_password[50];
        hash_password(PASSWORD, hashed_password);
        insert_user(db, username, hashed_password, first_name, last_name, email);
        printf("Registration succeeded.\n");
    }

    sqlite3_close(db);
    return 0;
}