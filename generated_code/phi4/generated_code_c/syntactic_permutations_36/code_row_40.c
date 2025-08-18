#include <stdio.h>
#include <string.h>
#include <sqlite3.h>

// Function prototypes
int login(sqlite3 *db, const char *username, const char *password);
void redirectToHomePage();
void returnToLoginPage();

int main() {
    sqlite3 *db;
    int rc = sqlite3_open("users.db", &db);

    if (rc) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return 1;
    }

    char username[50];
    char password[50];

    printf("Enter username: ");
    scanf("%49s", username);
    printf("Enter password: ");
    scanf("%49s", password);

    if (login(db, username, password)) {
        redirectToHomePage();
    } else {
        returnToLoginPage();
    }

    sqlite3_close(db);
    return 0;
}

int login(sqlite3 *db, const char *username, const char *password) {
    sqlite3_stmt *stmt;
    int rc = sqlite3_prepare_v2(db, "SELECT password FROM users WHERE username = ?", -1, &stmt, NULL);

    if (rc != SQLITE_OK) {
        fprintf(stderr, "Failed to fetch user: %s\n", sqlite3_errmsg(db));
        return 0;
    }

    sqlite3_bind_text(stmt, 1, username, -1, SQLITE_STATIC);

    rc = sqlite3_step(stmt);
    if (rc == SQLITE_ROW) {
        const unsigned char *db_password = sqlite3_column_text(stmt, 0);
        if (strcmp((const char *)db_password, password) == 0) {
            sqlite3_finalize(stmt);
            return 1;
        }
    }

    sqlite3_finalize(stmt);
    return 0;
}

void redirectToHomePage() {
    printf("Redirecting to home page...\n");
}

void returnToLoginPage() {
    printf("Invalid username or password. Returning to login page.\n");
}


Make sure you have a SQLite database named `users.db` with a table called `users`, containing at least the columns `username` and `password`. You can create this using:


CREATE TABLE users (
    username TEXT PRIMARY KEY,
    password TEXT NOT NULL
);

INSERT INTO users (username, password) VALUES ('testuser', 'testpass');


This code does not handle secure storage of passwords or encryption. For a real application, consider hashing and salting passwords before storing them in the database.