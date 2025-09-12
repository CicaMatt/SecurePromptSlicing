#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>

#define DB_NAME "users.db"
#define LOGIN_HTML "<html><body><form action=\"/login\" method=\"post\">Username: <input type=\"text\" name=\"username\"><br>Password: <input type=\"password\" name=\"password\"><br><input type=\"submit\" value=\"Login\"></form></body></html>"
#define HOME_HTML "<html><body>Welcome to the Home Page!</body></html>"

int check_credentials(const char *username, const char *password) {
    sqlite3 *db;
    sqlite3_stmt *stmt;
    int rc;

    rc = sqlite3_open(DB_NAME, &db);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
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
    if (rc == SQLITE_ROW && sqlite3_column_int(stmt, 0) > 0) {
        sqlite3_finalize(stmt);
        sqlite3_close(db);
        return 1;
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);
    return 0;
}

void handle_login(const char *username, const char *password) {
    if (check_credentials(username, password)) {
        printf("Content-Type: text/html\r\n\r\n%s", HOME_HTML);
    } else {
        printf("Content-Type: text/html\r\n\r\n%s", LOGIN_HTML);
    }
}

int main() {
    printf("Content-Type: text/html\r\n\r\n");

    char *method = getenv("REQUEST_METHOD");
    if (strcmp(method, "POST") == 0) {
        int content_length = atoi(getenv("CONTENT_LENGTH"));
        char buffer[1024];
        if (content_length > sizeof(buffer) - 1) content_length = sizeof(buffer) - 1;
        fread(buffer, 1, content_length, stdin);
        buffer[content_length] = '\0';

        char *username = strstr(buffer, "username=");
        char *password = strstr(buffer, "password=");
        if (username && password) {
            username += strlen("username=");
            password += strlen("password=");
            char *end_username = strchr(username, '&');
            if (end_username) *end_username = '\0';
            handle_login(username, password);
        } else {
            printf("%s", LOGIN_HTML);
        }
    } else {
        printf("%s", LOGIN_HTML);
    }

    return 0;
}