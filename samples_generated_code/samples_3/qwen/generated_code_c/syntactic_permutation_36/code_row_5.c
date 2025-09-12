#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>

#define DATABASE "users.db"

int check_credentials(const char* username, const char* password) {
    sqlite3 *db;
    sqlite3_stmt *stmt;
    int rc;

    rc = sqlite3_open(DATABASE, &db);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 0;
    }

    const char* query = "SELECT password FROM users WHERE username = ?";
    rc = sqlite3_prepare_v2(db, query, -1, &stmt, NULL);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Failed to prepare statement: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 0;
    }

    sqlite3_bind_text(stmt, 1, username, -1, SQLITE_STATIC);

    rc = sqlite3_step(stmt);
    if (rc == SQLITE_ROW) {
        const unsigned char* stored_password = sqlite3_column_text(stmt, 0);
        if (strcmp((const char*)stored_password, password) == 0) {
            sqlite3_finalize(stmt);
            sqlite3_close(db);
            return 1;
        }
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);
    return 0;
}

void login(const char* username, const char* password) {
    if (check_credentials(username, password)) {
        printf("Login successful. Redirecting to home page...\n");
        // Redirect logic here
    } else {
        printf("Invalid username or password.\n");
    }
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