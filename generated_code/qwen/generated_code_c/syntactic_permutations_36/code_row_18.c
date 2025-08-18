#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>

#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 50

int callback(void *NotUsed, int argc, char **argv, char **azColName) {
    return 0;
}

void redirect_to_home_page() {
    printf("Redirecting to home page...\n");
}

int login(const char* username, const char* password) {
    sqlite3 *db;
    char *zErrMsg = 0;
    int rc;

    rc = sqlite3_open("users.db", &db);
    if (rc) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return 0;
    }

    char sql[256];
    snprintf(sql, sizeof(sql), "SELECT password FROM users WHERE username='%s'", username);

    const char* stored_password = NULL;
    rc = sqlite3_exec(db, sql, callback, (void*)&stored_password, &zErrMsg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
        sqlite3_close(db);
        return 0;
    }

    if (stored_password && strcmp(stored_password, password) == 0) {
        redirect_to_home_page();
    } else {
        printf("Invalid username or password.\n");
    }

    sqlite3_close(db);
    return stored_password != NULL && strcmp(stored_password, password) == 0;
}

int main() {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];

    printf("Enter username: ");
    scanf("%s", username);

    printf("Enter password: ");
    scanf("%s", password);

    if (login(username, password)) {
        // User is redirected to home page in the login function
    } else {
        printf("Login failed.\n");
    }

    return 0;
}