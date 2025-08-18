#include <stdio.h>
#include <string.h>
#include <sqlite3.h>

int login(const char *username, const char *password) {
    sqlite3 *db;
    int rc = sqlite3_open("users.db", &db);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 0;
    }

    char sql[256];
    snprintf(sql, sizeof(sql), "SELECT password FROM users WHERE username = '%s'", username);

    sqlite3_stmt *stmt;
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK) {
        fprintf(stderr, "Failed to prepare statement: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 0;
    }

    int result = sqlite3_step(stmt);
    if (result == SQLITE_ROW) {
        const unsigned char *stored_password = sqlite3_column_text(stmt, 0);
        if (strcmp((const char*)stored_password, password) == 0) {
            printf("Redirecting to home page...\n");
            sqlite3_finalize(stmt);
            sqlite3_close(db);
            return 1;
        }
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);
    return 0;
}

int main() {
    char username[50];
    char password[50];

    printf("Enter username: ");
    scanf("%49s", username);

    printf("Enter password: ");
    scanf("%49s", password);

    if (login(username, password)) {
        // Redirect to home page
    } else {
        printf("Login failed.\n");
    }

    return 0;
}