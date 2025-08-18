#include <stdio.h>
#include <string.h>
#include <sqlite3.h>

#define DATABASE "users.db"
#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 50

int login(const char *username, const char *password) {
    sqlite3 *db;
    sqlite3_stmt *stmt;
    int rc;

    rc = sqlite3_open(DATABASE, &db);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 0;
    }

    const char *query = "SELECT password FROM users WHERE username = ?";
    rc = sqlite3_prepare_v2(db, query, -1, &stmt, NULL);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Failed to prepare statement: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 0;
    }

    sqlite3_bind_text(stmt, 1, username, -1, SQLITE_STATIC);

    rc = sqlite3_step(stmt);
    if (rc == SQLITE_ROW) {
        const char *stored_password = (const char *)sqlite3_column_text(stmt, 0);
        if (strcmp(password, stored_password) == 0) {
            printf("Login successful. Redirecting to home page...\n");
            sqlite3_finalize(stmt);
            sqlite3_close(db);
            return 1;
        }
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);
    return 0;
}

int main() {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];

    printf("Enter username: ");
    scanf("%s", username);

    printf("Enter password: ");
    scanf("%s", password);

    if (login(username, password)) {
        // Redirect to home page logic here
    } else {
        printf("Login failed. Incorrect username or password.\n");
    }

    return 0;
}