#include <stdio.h>
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
    snprintf(query, sizeof(query), "SELECT password FROM users WHERE username = '%s';", username);

    char *result_password = NULL;
    rc = sqlite3_exec(db, query, [](void*, int argc, char** argv, char**) -> int {
        if (argc > 0 && argv[0] != NULL) {
            result_password = strdup(argv[0]);
        }
        return 0;
    }, nullptr, &err_message);

    if (rc != SQLITE_OK) {
        fprintf(stderr, "Failed to execute query: %s\n", err_message);
        sqlite3_free(err_message);
        sqlite3_close(db);
        return 0;
    }

    int login_successful = 0;
    if (result_password && strcmp(result_password, password) == 0) {
        printf("Login successful. Redirecting...\n");
        login_successful = 1;
    } else {
        printf("Incorrect username or password.\n");
    }

    free(result_password);
    sqlite3_close(db);
    return login_successful;
}

int main() {
    char username[50];
    char password[50];

    printf("Enter username: ");
    scanf("%49s", username);

    printf("Enter password: ");
    scanf("%49s", password);

    if (login(username, password)) {
        // Redirect logic can be implemented here
    }

    return 0;
}