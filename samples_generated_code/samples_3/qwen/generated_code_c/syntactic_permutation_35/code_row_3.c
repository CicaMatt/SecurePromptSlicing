#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>

#define DATABASE "users.db"

int check_credentials(const char *username, const char *password) {
    sqlite3 *db;
    sqlite3_stmt *stmt;
    int rc;

    rc = sqlite3_open(DATABASE, &db);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 0;
    }

    const char *sql = "SELECT * FROM users WHERE username = ? AND password = ?";
    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Failed to prepare statement: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 0;
    }

    sqlite3_bind_text(stmt, 1, username, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, password, -1, SQLITE_STATIC);

    rc = sqlite3_step(stmt);
    int exists = (rc == SQLITE_ROW);

    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return exists;
}

int main() {
    const char *username = "testuser"; // This should be retrieved from the form
    const char *password = "testpass"; // This should be retrieved from the form

    if (check_credentials(username, password)) {
        printf("Content-Type: text/html\n\n");
        printf("<html><head><title>Redirecting...</title></head>");
        printf("<body>");
        printf("<script>window.location.href='/home.html';</script>");
        printf("</body></html>");
    } else {
        printf("Content-Type: text/html\n\n");
        printf("<html><head><title>Login Failed</title></head>");
        printf("<body>");
        printf("<h1>Login Failed</h1>");
        printf("<p>Invalid username or password. <a href='/login.html'>Try again</a>.</p>");
        printf("</body></html>");
    }

    return 0;
}