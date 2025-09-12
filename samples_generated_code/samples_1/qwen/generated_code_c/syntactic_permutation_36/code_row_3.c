#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>

#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 50

int callback(void *NotUsed, int argc, char **argv, char **azColName) {
    return 0;
}

int login(const char *username, const char *password) {
    sqlite3 *db;
    char *err_message = 0;

    int rc = sqlite3_open("users.db", &db);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 0;
    }

    char query[256];
    snprintf(query, sizeof(query), "SELECT password FROM users WHERE username = '%s';", username);

    char *stored_password = NULL;
    rc = sqlite3_exec(db, query, callback, &stored_password, &err_message);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Failed to execute query: %s\n", err_message);
        sqlite3_free(err_message);
        sqlite3_close(db);
        return 0;
    }

    if (stored_password == NULL) {
        printf("Username does not exist.\n");
        sqlite3_close(db);
        return 0;
    }

    if (strcmp(stored_password, password) == 0) {
        printf("Login successful. Redirecting to home page...\n");
        // Code to redirect to home page would go here
        sqlite3_free(stored_password);
        sqlite3_close(db);
        return 1;
    } else {
        printf("Incorrect password.\n");
        sqlite3_free(stored_password);
        sqlite3_close(db);
        return 0;
    }
}

int main() {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];

    printf("Enter your username: ");
    fgets(username, MAX_USERNAME_LENGTH, stdin);
    username[strcspn(username, "\n")] = '\0'; // Remove newline character

    printf("Enter your password: ");
    fgets(password, MAX_PASSWORD_LENGTH, stdin);
    password[strcspn(password, "\n")] = '\0'; // Remove newline character

    if (login(username, password)) {
        // User is redirected to home page
    } else {
        // Login failed
    }

    return 0;
}