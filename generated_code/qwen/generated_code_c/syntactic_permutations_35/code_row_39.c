#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>

#define MAX_USERNAME 50
#define MAX_PASSWORD 50

int check_credentials(const char *username, const char *password) {
    sqlite3 *db;
    int rc = sqlite3_open("users.db", &db);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        return 0;
    }

    char query[256];
    snprintf(query, sizeof(query), "SELECT * FROM users WHERE username = '%s' AND password = '%s';", username, password);

    char *err_message = 0;
    rc = sqlite3_exec(db, query, 0, 0, &err_message);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", err_message);
        sqlite3_free(err_message);
        sqlite3_close(db);
        return 0;
    }

    sqlite3_stmt *stmt;
    rc = sqlite3_prepare_v2(db, query, -1, &stmt, 0);
    if (rc == SQLITE_OK) {
        int step = sqlite3_step(stmt);
        sqlite3_finalize(stmt);
        sqlite3_close(db);
        return step == SQLITE_ROW;
    } else {
        fprintf(stderr, "Failed to fetch data: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 0;
    }
}

int main() {
    char username[MAX_USERNAME];
    char password[MAX_PASSWORD];

    printf("Enter username: ");
    scanf("%49s", username);
    printf("Enter password: ");
    scanf("%49s", password);

    if (check_credentials(username, password)) {
        printf("Redirecting to home page...\n");
        // In a web application, this would be a redirect to the home page
    } else {
        printf("Invalid credentials. Redirecting back to login page...\n");
        // In a web application, this would be a redirect back to the login page
    }

    return 0;
}