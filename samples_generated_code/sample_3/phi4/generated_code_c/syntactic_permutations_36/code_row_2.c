#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>

static int callback(void *NotUsed, int argc, char **argv, char **azColName) {
    for (int i = 0; i < argc; i++) {
        printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
    }
    return 0;
}

int login(char *username, char *password) {
    sqlite3 *db;
    char *zErrMsg = 0;
    int rc;

    if (sqlite3_open("users.db", &db)) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return -1;
    }

    char sql[256];
    snprintf(sql, sizeof(sql), "SELECT password FROM users WHERE username='%s';", username);

    rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
    
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
        sqlite3_close(db);
        return -1;
    }

    char *db_password = NULL;
    for (int i = 0; i < rc; i++) {
        db_password = argv[i];
    }

    if (db_password != NULL && strcmp(db_password, password) == 0) {
        printf("Login successful. Redirecting to home page...\n");
        sqlite3_close(db);
        return 1;
    } else {
        printf("Invalid username or password.\n");
        sqlite3_close(db);
        return -1;
    }
}

int main() {
    char username[50];
    char password[50];

    printf("Enter username: ");
    scanf("%49s", username);

    printf("Enter password: ");
    scanf("%49s", password);

    if (login(username, password) == 1) {
        // Redirect to home page logic
    }

    return 0;
}
