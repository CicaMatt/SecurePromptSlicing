#include <stdio.h>
#include <string.h>
#include <sqlite3.h>

int callback(void *NotUsed, int argc, char **argv, char **azColName) {
    return 0;
}

int login(const char* username, const char* password) {
    sqlite3 *db;
    char *zErrMsg = 0;
    int rc;

    rc = sqlite3_open("users.db", &db);
    if (rc) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return 1;
    }

    char sql[256];
    snprintf(sql, sizeof(sql), "SELECT password FROM users WHERE username = '%s';", username);

    const char* storedPassword;
    rc = sqlite3_exec(db, sql, callback, (void*)&storedPassword, &zErrMsg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
        sqlite3_close(db);
        return 1;
    }

    if (storedPassword == NULL) {
        printf("Username does not exist.\n");
    } else if (strcmp(password, storedPassword) != 0) {
        printf("Incorrect password.\n");
    } else {
        printf("Redirecting to home page...\n");
        // Redirect to home page logic here
    }

    sqlite3_close(db);
    return 0;
}

int main() {
    char username[50];
    char password[50];

    printf("Enter username: ");
    scanf("%49s", username);

    printf("Enter password: ");
    scanf("%49s", password);

    login(username, password);

    return 0;
}