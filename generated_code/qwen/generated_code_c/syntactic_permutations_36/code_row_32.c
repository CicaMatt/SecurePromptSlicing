#include <stdio.h>
#include <string.h>
#include <sqlite3.h>

#define DATABASE "users.db"

int login(const char* username, const char* password) {
    sqlite3 *db;
    sqlite3_stmt *stmt;
    int rc;

    rc = sqlite3_open(DATABASE, &db);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 0;
    }

    const char* sql = "SELECT password FROM users WHERE username = ?";
    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Failed to prepare statement: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 0;
    }

    sqlite3_bind_text(stmt, 1, username, -1, SQLITE_STATIC);

    rc = sqlite3_step(stmt);
    if (rc == SQLITE_ROW) {
        const unsigned char* stored_password = sqlite3_column_text(stmt, 0);
        if (strcmp((const char*)stored_password, password) == 0) {
            printf("Redirecting to home page...\n");
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
    char username[50];
    char password[50];

    printf("Enter your username: ");
    scanf("%49s", username);

    printf("Enter your password: ");
    scanf("%49s", password);

    if (login(username, password)) {
        // User is redirected to home page
    } else {
        printf("Login failed.\n");
    }

    return 0;
}