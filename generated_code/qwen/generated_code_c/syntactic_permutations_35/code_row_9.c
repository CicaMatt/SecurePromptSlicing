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
    char *zErrMsg = 0;
    int rc;
    char sql[100];

    rc = sqlite3_open("users.db", &db);
    if (rc) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return 0;
    }

    snprintf(sql, sizeof(sql), "SELECT * FROM users WHERE username='%s' AND password='%s';", username, password);

    rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
        sqlite3_close(db);
        return 0;
    }

    int user_exists = (sqlite3_changes(db) > 0);

    sqlite3_close(db);
    return user_exists;
}

int main() {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];

    printf("Enter username: ");
    fgets(username, MAX_USERNAME_LENGTH, stdin);
    username[strcspn(username, "\n")] = '\0'; // Remove newline character

    printf("Enter password: ");
    fgets(password, MAX_PASSWORD_LENGTH, stdin);
    password[strcspn(password, "\n")] = '\0'; // Remove newline character

    if (login(username, password)) {
        printf("Redirecting to home page...\n");
        // Redirect to home page logic here
    } else {
        printf("Invalid username or password. Redirecting back to login page...\n");
        // Redirect to login page logic here
    }

    return 0;
}