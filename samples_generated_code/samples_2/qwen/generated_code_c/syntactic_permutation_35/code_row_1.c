#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>

#define DATABASE "users.db"
#define LOGIN_SUCCESS "home.html"
#define LOGIN_FAILURE "login.html"

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

    const char *sql = "SELECT COUNT(*) FROM users WHERE username = ? AND password = ?";
    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Failed to prepare statement: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 0;
    }

    sqlite3_bind_text(stmt, 1, username, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, password, -1, SQLITE_STATIC);

    rc = sqlite3_step(stmt);
    if (rc == SQLITE_ROW) {
        int count = sqlite3_column_int(stmt, 0);
        sqlite3_finalize(stmt);
        sqlite3_close(db);
        return count > 0;
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);
    return 0;
}

int main() {
    const char *username = getenv("QUERY_STRING");
    const char *password = strchr(username, '&') + 1;

    // Simple parsing of query string
    if (strchr(username, '=')) {
        username = strchr(username, '=') + 1;
        if (strchr(password, '=')) {
            password = strchr(password, '=') + 1;
        } else {
            fprintf(stderr, "Invalid password format\n");
            return 1;
        }
    } else {
        fprintf(stderr, "Invalid username format\n");
        return 1;
    }

    int valid_credentials = check_credentials(username, password);

    printf("Content-Type: text/html\n\n");

    if (valid_credentials) {
        printf("<meta http-equiv=\"refresh\" content=\"0; url=%s\">", LOGIN_SUCCESS);
    } else {
        printf("<meta http-equiv=\"refresh\" content=\"0; url=%s\">", LOGIN_FAILURE);
    }

    return 0;
}