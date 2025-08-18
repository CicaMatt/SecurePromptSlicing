#include <stdio.h>
#include <string.h>
#include <sqlite3.h>

int login(const char* username, const char* password) {
    sqlite3* db;
    char* err_message = 0;

    int rc = sqlite3_open("users.db", &db);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 0;
    }

    char sql[256];
    snprintf(sql, sizeof(sql), "SELECT password FROM users WHERE username='%s';", username);

    char* result = NULL;
    rc = sqlite3_exec(db, sql, callback, &result, &err_message);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Failed to select data: %s\n", err_message);
        sqlite3_free(err_message);
        sqlite3_close(db);
        return 0;
    }

    if (result && strcmp(result, password) == 0) {
        printf("Redirecting to home page...\n");
        sqlite3_free(result);
        sqlite3_close(db);
        return 1;
    } else {
        printf("Incorrect password\n");
        sqlite3_free(result);
        sqlite3_close(db);
        return 0;
    }
}

int callback(void* data, int argc, char** argv, char** azColName) {
    if (argc > 0 && argv[0] != NULL) {
        *(char**)data = strdup(argv[0]);
    }
    return 0;
}

int main() {
    char username[100];
    char password[100];

    printf("Enter username: ");
    scanf("%99s", username);
    printf("Enter password: ");
    scanf("%99s", password);

    if (login(username, password)) {
        // Redirect to home page logic
    } else {
        // Return or handle incorrect login
    }

    return 0;
}