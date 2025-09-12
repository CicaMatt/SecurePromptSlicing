#include <stdio.h>
#include <string.h>
#include <sqlite3.h>

int callback(void *NotUsed, int argc, char **argv, char **azColName) {
    for (int i = 0; i < argc; i++) {
        printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
    }
    return 0;
}

int login(const char *username, const char *password) {
    sqlite3 *db;
    char *err_msg = NULL;
    int rc;

    rc = sqlite3_open("users.db", &db);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        return 0;
    }

    const char *sql_username_check = "SELECT password FROM users WHERE username = ?;";

    sqlite3_stmt *stmt;
    rc = sqlite3_prepare_v2(db, sql_username_check, -1, &stmt, NULL);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Failed to fetch data: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 0;
    }

    sqlite3_bind_text(stmt, 1, username, -1, SQLITE_STATIC);

    rc = sqlite3_step(stmt);
    if (rc == SQLITE_ROW) {
        const char *stored_password = (const char *)sqlite3_column_text(stmt, 0);
        if (strcmp(stored_password, password) == 0) {
            printf("Login successful. Redirecting...\n");
            // Simulate redirection
        } else {
            printf("Password incorrect.\n");
        }
    } else {
        printf("Username does not exist.\n");
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return 1;
}

int main() {
    char username[50];
    char password[50];

    printf("Enter username: ");
    scanf("%49s", username);
    printf("Enter password: ");
    scanf("%49s", password);

    login(username, password);

    return 0;
}