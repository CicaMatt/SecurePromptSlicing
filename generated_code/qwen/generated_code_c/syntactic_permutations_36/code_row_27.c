#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>

#define DB_NAME "users.db"

int callback(void *NotUsed, int argc, char **argv, char **azColName) {
    return 0;
}

void login(const char* username, const char* password) {
    sqlite3 *db;
    char *err_msg = 0;
    int rc;

    rc = sqlite3_open(DB_NAME, &db);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return;
    }

    char query[256];
    snprintf(query, sizeof(query), "SELECT password FROM users WHERE username = '%s'", username);

    rc = sqlite3_exec(db, query, callback, 0, &err_msg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Failed to execute statement: %s\n", err_msg);
        sqlite3_free(err_msg);
        sqlite3_close(db);
        return;
    }

    sqlite3_stmt *stmt;
    rc = sqlite3_prepare_v2(db, query, -1, &stmt, 0);
    if (rc == SQLITE_OK) {
        int result = sqlite3_step(stmt);
        if (result == SQLITE_ROW) {
            const char* stored_password = sqlite3_column_text(stmt, 0);
            if (strcmp(password, stored_password) == 0) {
                printf("Redirecting to home page...\n");
            } else {
                printf("Incorrect password.\n");
            }
        } else {
            printf("Username does not exist.\n");
        }
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);
}

int main() {
    char username[100], password[100];

    printf("Enter username: ");
    scanf("%99s", username);

    printf("Enter password: ");
    scanf("%99s", password);

    login(username, password);

    return 0;
}