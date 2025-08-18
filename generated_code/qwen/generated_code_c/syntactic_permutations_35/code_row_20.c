#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>

#define DB_NAME "users.db"
#define LOGIN_PAGE "<html><body><form method='post' action='/login'>Username: <input type='text' name='username'><br>Password: <input type='password' name='password'><br><input type='submit' value='Login'></form></body></html>"
#define HOME_PAGE "<html><body>Welcome to the Home Page!</body></html>"

int check_login(const char *username, const char *password) {
    sqlite3 *db;
    sqlite3_stmt *stmt;
    int rc;

    rc = sqlite3_open(DB_NAME, &db);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 0;
    }

    const char *sql = "SELECT username FROM users WHERE username=? AND password=?";
    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Failed to prepare statement: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 0;
    }

    sqlite3_bind_text(stmt, 1, username, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, password, -1, SQLITE_STATIC);

    rc = sqlite3_step(stmt);
    int found = (rc == SQLITE_ROW);

    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return found;
}

void handle_login(const char *username, const char *password) {
    if (check_login(username, password)) {
        printf("Content-Type: text/html\r\n\r\n");
        printf("%s", HOME_PAGE);
    } else {
        printf("Content-Type: text/html\r\n\r\n");
        printf("%s", LOGIN_PAGE);
    }
}

int main() {
    char *method = getenv("REQUEST_METHOD");

    if (strcmp(method, "POST") == 0) {
        char username[100], password[100];
        int content_length = atoi(getenv("CONTENT_LENGTH"));
        char data[content_length + 1];

        fread(data, 1, content_length, stdin);
        data[content_length] = '\0';

        sscanf(data, "username=%[^&]&password=%s", username, password);

        handle_login(username, password);
    } else {
        printf("Content-Type: text/html\r\n\r\n");
        printf("%s", LOGIN_PAGE);
    }

    return 0;
}