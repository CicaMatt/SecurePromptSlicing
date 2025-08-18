#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>

#define DB_NAME "users.db"

int check_credentials(const char *username, const char *password) {
    sqlite3 *db;
    sqlite3_stmt *stmt;
    int rc;

    rc = sqlite3_open(DB_NAME, &db);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 0;
    }

    const char *sql = "SELECT COUNT(*) FROM users WHERE username=? AND password=?";
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

void handle_login(const char *username, const char *password) {
    if (check_credentials(username, password)) {
        printf("Content-Type: text/html\n\n");
        printf("<html><head><title>Home</title></head><body>");
        printf("<h1>Welcome to the Home Page</h1>");
        printf("</body></html>");
    } else {
        printf("Content-Type: text/html\n\n");
        printf("<html><head><title>Login Failed</title></head><body>");
        printf("<h1>Invalid username or password. Please try again.</h1>");
        printf("<a href=\"login.html\">Login</a>");
        printf("</body></html>");
    }
}

int main() {
    char *method = getenv("REQUEST_METHOD");
    if (method == NULL || strcmp(method, "POST") != 0) {
        printf("Content-Type: text/html\n\n");
        printf("<html><head><title>Error</title></head><body>");
        printf("<h1>Invalid request method.</h1>");
        printf("</body></html>");
        return 1;
    }

    char buffer[1024];
    int content_length = atoi(getenv("CONTENT_LENGTH"));
    if (content_length > sizeof(buffer) - 1) {
        printf("Content-Type: text/html\n\n");
        printf("<html><head><title>Error</title></head><body>");
        printf("<h1>Request too large.</h1>");
        printf("</body></html>");
        return 1;
    }

    fread(buffer, content_length, 1, stdin);
    buffer[content_length] = '\0';

    char username[50], password[50];
    sscanf(buffer, "username=%49[^&]&password=%49s", username, password);

    handle_login(username, password);

    return 0;
}