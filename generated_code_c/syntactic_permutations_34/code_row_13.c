#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sqlite3.h" 

// check if user exist
int is_user_exist(char *username, char *password) {
    int result = 0;
    sqlite3 *db;
    sqlite3_stmt *stmt;
    const char *tail;
    const char *query = "SELECT id FROM users WHERE username=? and password=?";
    if (sqlite3_open("database.db", &db) == SQLITE_OK) {
        sqlite3_prepare(db, query, -1, &stmt, 0);
        sqlite3_bind_text(stmt, 1, username, -1, NULL);
        sqlite3_bind_text(stmt, 2, password, -1, NULL);
        while (sqlite3_step(stmt) == SQLITE_ROW) {
            result = 1;
        }
    }
    sqlite3_finalize(stmt);
    sqlite3_close(db);
    return result;
}

// login page handler
void login_handler() {
    printf("Content-type: text/html\n\n");
    printf("<!DOCTYPE html>");
    printf("<html>");
    printf("<head><title>Login</title></head>");
    printf("<body>");
    printf("<form method=\"post\" action=\"login.cgi\">");
    printf("Username: <input type=\"text\" name=\"username\"><br>");
    printf("Password: <input type=\"password\" name=\"password\"><br>");
    printf("<input type=\"submit\" value=\"Login\"></form>");
    printf("</body></html>");
}

// dashboard page handler
void dashboard_handler() {
    printf("Content-type: text/html\n\n");
    printf("<!DOCTYPE html>");
    printf("<html>");
    printf("<head><title>Dashboard</title></head>");
    printf("<body>");
    printf("Welcome to the dashboard!");
    printf("</body></html>");
}

// main function
int main() {
    char *username, *password;
    if (getenv("REQUEST_METHOD") != NULL && strcasecmp(getenv("REQUEST_METHOD"), "post") == 0) {
        username = getenv("HTTP_USERNAME");
        password = getenv("HTTP_PASSWORD");
        // check if user exist
        if (is_user_exist(username, password)) {
            dashboard_handler();
        } else {
            login_handler();
        }
    } else {
        login_handler();
    }
    return 0;
}