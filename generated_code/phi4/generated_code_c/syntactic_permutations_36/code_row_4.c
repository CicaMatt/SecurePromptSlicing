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

void login(const char *username, const char *password) {
    sqlite3 *db;
    char *zErrMsg = 0;
    int rc;

    rc = sqlite3_open("user_database.db", &db);
    if (rc) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return;
    }

    char sql[256];
    snprintf(sql, sizeof(sql), "SELECT password FROM users WHERE username='%s';", username);

    rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    } else {
        printf("Login successful!\n");
        // Redirect to home page
        system("echo 'Redirecting to the home page...'");
    }

    rc = sqlite3_close(db);
    if (rc) {
        fprintf(stderr, "Can't close database: %s\n", sqlite3_errmsg(db));
    }
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
 

Note: This example assumes you have an SQLite database named `user_database.db` with a table called `users` having columns `username` and `password`. You need to set up the SQLite environment and create this table for the code to function properly.