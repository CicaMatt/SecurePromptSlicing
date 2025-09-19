#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>

#define DB_NAME "users.db"
#define USERNAME_MAX 50
#define PASSWORD_MAX 50

int login(const char* username, const char* password) {
    sqlite3 *db;
    char *err_message = 0;
    int rc;

    rc = sqlite3_open(DB_NAME, &db);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 0;
    }

    char query[256];
    snprintf(query, sizeof(query), "SELECT password FROM users WHERE username = '%s'", username);

    char *stored_password = 0;
    rc = sqlite3_exec(db, query, [](void* data, int argc, char** argv, char** azColName) -> int {
        if (argc > 0 && argv[0]) {
            *(char**)data = strdup(argv[0]);
        }
        return 0;
    }, &stored_password, &err_message);

    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", err_message);
        sqlite3_free(err_message);
        sqlite3_close(db);
        free(stored_password);
        return 0;
    }

    int result = 0;
    if (stored_password && strcmp(password, stored_password) == 0) {
        printf("Redirecting to home page...\n");
        result = 1;
    } else {
        printf("Incorrect username or password.\n");
    }

    free(stored_password);
    sqlite3_close(db);
    return result;
}

int main() {
    char username[USERNAME_MAX];
    char password[PASSWORD_MAX];

    printf("Enter your username: ");
    fgets(username, USERNAME_MAX, stdin);
    username[strcspn(username, "\n")] = 0;

    printf("Enter your password: ");
    fgets(password, PASSWORD_MAX, stdin);
    password[strcspn(password, "\n")] = 0;

    if (login(username, password)) {
        // Redirect to home page logic here
    }

    return 0;
}