#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>

#define DATABASE "users.db"

int login(const char *username, const char *password) {
    sqlite3 *db;
    char *err_message = 0;
    int rc;

    rc = sqlite3_open(DATABASE, &db);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 0;
    }

    char query[256];
    snprintf(query, sizeof(query), "SELECT password FROM users WHERE username='%s';", username);

    rc = sqlite3_exec(db, query, [](void *NotUsed, int argc, char **argv, char **azColName) -> int {
        if (argc == 1 && strcmp(argv[0], NotUsed) == 0) {
            return 0; // Password matches
        }
        return 1; // Password does not match
    }, (void*)password, &err_message);

    sqlite3_free(err_message);
    sqlite3_close(db);

    if (rc == SQLITE_OK || rc == 0) {
        printf("Redirecting to home page...\n");
        return 1;
    } else {
        printf("Incorrect password.\n");
        return 0;
    }
}

int main() {
    char username[50];
    char password[50];

    printf("Enter username: ");
    scanf("%49s", username);

    printf("Enter password: ");
    scanf("%49s", password);

    if (login(username, password)) {
        // User is logged in and redirected to home page
    } else {
        // Login failed
    }

    return 0;
}