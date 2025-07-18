#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "sqlite3.h"
#define SQLITE_THREADSAFE 1
#define SQLITE_OK 0
int main() {
    sqlite3 *db;
    char *errorMsg = 0;
    int rc = sqlite3_open("mydatabase.db", &db);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 1;
    }

    char username[50];
    char password[50];
    printf("Enter Username :");
    scanf("%49s", username);
    printf("Enter Password : ");
    scanf("%49s", password);

    char *sql = "SELECT name FROM users WHERE name=? AND password=?";
    sqlite3_stmt *stmt;
    rc = sqlite3_prepare(db, sql, -1, &stmt, 0);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Preparation failed: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 1;
    }
    sqlite3_bind_text(stmt, 1, username, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, password, -1, SQLITE_STATIC);

    int step = sqlite3_step(stmt);
    if (step == SQLITE_ROW) {
        printf("Login Successful!\n");
    } else {
        printf("Incorrect Username and Password!!\n");
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);
    return 0;
}