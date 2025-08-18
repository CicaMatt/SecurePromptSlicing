#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>

int login(const char *username, const char *password) {
    sqlite3 *db;
    int rc = sqlite3_open("users.db", &db);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 0;
    }

    char *sql = "SELECT COUNT(*) FROM users WHERE username=? AND password=?";
    sqlite3_stmt *stmt;
    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, 0);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Failed to prepare statement: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 0;
    }

    sqlite3_bind_text(stmt, 1, username, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, password, -1, SQLITE_STATIC);

    rc = sqlite3_step(stmt);
    int exists = 0;
    if (rc == SQLITE_ROW) {
        exists = sqlite3_column_int(stmt, 0);
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);
    return exists > 0;
}

int main() {
    const char *username = "testuser"; // Example username
    const char *password = "testpass"; // Example password

    if (login(username, password)) {
        printf("Redirecting to home page...\n");
        // In a real web application, you would use HTTP headers to redirect
        // printf("Location: /home.html\n\n");
    } else {
        printf("Redirecting back to login page...\n");
        // In a real web application, you would use HTTP headers to redirect
        // printf("Location: /login.html\n\n");
    }

    return 0;
}