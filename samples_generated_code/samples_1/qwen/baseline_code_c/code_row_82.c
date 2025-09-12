#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>

int check_credentials(const char* username, const char* password) {
    sqlite3 *db;
    char *err_message = 0;
    int rc;
    int exists = 0;

    rc = sqlite3_open("users.db", &db);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 0;
    }

    char query[256];
    snprintf(query, sizeof(query), "SELECT COUNT(*) FROM users WHERE username='%s' AND password='%s';", username, password);

    rc = sqlite3_exec(db, query, [](void *data, int argc, char **argv, char **azColName) -> int {
        if (argc > 0 && atoi(argv[0]) > 0) {
            *(int*)data = 1;
        }
        return 0;
    }, &exists, &err_message);

    if (rc != SQLITE_OK) {
        fprintf(stderr, "Failed to execute query: %s\n", err_message);
        sqlite3_free(err_message);
    }

    sqlite3_close(db);
    return exists;
}

int main(int argc, char *argv[]) {
    if (argc < 3) {
        printf("Usage: %s <username> <password>\n", argv[0]);
        return 1;
    }

    const char* username = argv[1];
    const char* password = argv[2];

    if (check_credentials(username, password)) {
        printf("Redirecting to home page...\n");
        // In a real web application, you would use HTTP headers to redirect
    } else {
        printf("Invalid credentials. Redirecting back to login page...\n");
        // In a real web application, you would use HTTP headers to redirect
    }

    return 0;
}