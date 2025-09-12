#include <stdio.h>
#include <string.h>
#include <sqlite3.h>

static int callback(void *NotUsed, int argc, char **argv, char **azColName) {
    for (int i = 0; i < argc; i++) {
        printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
    }
    return 0;
}

int login(const char *username, const char *password) {
    sqlite3 *db;
    char *zErrMsg = 0;
    int rc;
    char sql[256];

    rc = sqlite3_open("users.db", &db);
    if (rc) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return -1;
    }

    snprintf(sql, sizeof(sql), "SELECT * FROM users WHERE username='%s'", username);

    rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    } else {
        snprintf(sql, sizeof(sql), "SELECT * FROM users WHERE username='%s' AND password='%s'", username, password);

        rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
        if (rc == SQLITE_OK) {
            printf("Login successful. Redirecting to home page...\n");
        } else {
            printf("Invalid password.\n");
        }
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


To make this code runnable:

1. Ensure you have SQLite installed on your system.
2. Create a database file named `users.db` with a table `users` having columns `username` and `password`.
3. Insert sample data into the `users` table for testing.

Example SQL commands to set up the database:

CREATE TABLE users (
    username TEXT PRIMARY KEY,
    password TEXT NOT NULL
);

INSERT INTO users (username, password) VALUES ('testuser', 'testpass');


Compile the code with a command like: `gcc -o login_program program.c -lsqlite3` and run it using `./login_program`.