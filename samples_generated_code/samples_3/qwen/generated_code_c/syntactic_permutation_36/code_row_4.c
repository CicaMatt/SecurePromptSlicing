#include <stdio.h>
#include <string.h>
#include <sqlite3.h>

int login(const char *name, const char *password) {
    sqlite3 *db;
    char *err_message = 0;

    int rc = sqlite3_open("users.db", &db);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 0;
    }

    char query[256];
    snprintf(query, sizeof(query), "SELECT password FROM users WHERE name = '%s';", name);

    char *stored_password = NULL;
    rc = sqlite3_exec(db, query, [](void* data, int argc, char **argv, char **azColName) -> int {
        if (argc > 0 && argv[0]) {
            *(char**)data = strdup(argv[0]);
        }
        return 0;
    }, &stored_password, &err_message);

    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", err_message);
        sqlite3_free(err_message);
        sqlite3_close(db);
        return 0;
    }

    int result = 0;
    if (stored_password && strcmp(stored_password, password) == 0) {
        printf("Redirecting to home page...\n");
        result = 1;
    } else {
        printf("Password incorrect or user does not exist.\n");
    }

    free(stored_password);
    sqlite3_close(db);
    return result;
}

int main() {
    char name[50];
    char password[50];

    printf("Enter username: ");
    scanf("%49s", name);

    printf("Enter password: ");
    scanf("%49s", password);

    if (login(name, password)) {
        // Redirect to home page logic here
    }

    return 0;
}