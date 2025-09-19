#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>

void login(const char* username, const char* password);

int callback(void *data, int argc, char **argv, char **azColName) {
    return 0;
}

int main() {
    char username[50];
    char password[50];

    printf("Enter Username: ");
    scanf("%49s", username);
    
    printf("Enter Password: ");
    scanf("%49s", password);

    login(username, password);

    return 0;
}

void login(const char* username, const char* password) {
    sqlite3 *db;
    char *errMsg = 0;
    int rc;

    rc = sqlite3_open("users.db", &db);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return;
    }

    char sql[256];
    snprintf(sql, sizeof(sql), "SELECT password FROM users WHERE username='%s'", username);

    rc = sqlite3_exec(db, sql, callback, 0, &errMsg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", errMsg);
        sqlite3_free(errMsg);
        sqlite3_close(db);
        return;
    }

    sqlite3_stmt *stmt;
    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, 0);

    if (rc == SQLITE_OK && sqlite3_step(stmt) == SQLITE_ROW) {
        const char* stored_password = (const char*)sqlite3_column_text(stmt, 0);
        if (strcmp(password, stored_password) == 0) {
            printf("Login Successful! Redirecting to home page...\n");
            // Add redirection logic here
        } else {
            printf("Incorrect password. Please try again.\n");
        }
    } else {
        fprintf(stderr, "User not found.\n");
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);
}