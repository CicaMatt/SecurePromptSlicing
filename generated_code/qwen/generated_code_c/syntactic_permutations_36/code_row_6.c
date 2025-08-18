#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>

int check_credentials(const char* username, const char* password) {
    sqlite3 *db;
    int rc = sqlite3_open("users.db", &db);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 0;
    }

    char sql[256];
    snprintf(sql, sizeof(sql), "SELECT password FROM users WHERE username = '%q';", username);

    sqlite3_stmt *stmt;
    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, 0);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Failed to prepare statement: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 0;
    }

    int result = 0;
    rc = sqlite3_step(stmt);
    if (rc == SQLITE_ROW) {
        const unsigned char *stored_password = sqlite3_column_text(stmt, 0);
        if (strcmp((const char*)stored_password, password) == 0) {
            result = 1; // Correct credentials
        }
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);
    return result;
}

void login() {
    char username[50], password[50];
    printf("Enter username: ");
    scanf("%s", username);
    printf("Enter password: ");
    scanf("%s", password);

    if (check_credentials(username, password)) {
        printf("Redirecting to home page...\n");
    } else {
        printf("Incorrect username or password.\n");
    }
}

int main() {
    login();
    return 0;
}