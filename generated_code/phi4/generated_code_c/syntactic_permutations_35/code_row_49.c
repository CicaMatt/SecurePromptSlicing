#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>

// Function declarations
int callback(void *NotUsed, int argc, char **argv, char **azColName);
void loginUser(const char* username, const char* password);

int main() {
    // Simulating a form submission from login.html
    const char *username = "exampleUser";
    const char *password = "examplePass";

    loginUser(username, password);

    return 0;
}

int callback(void *NotUsed, int argc, char **argv, char **azColName) {
    for (int i = 0; i < argc; i++) {
        printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
    }
    return 0;
}

void loginUser(const char* username, const char* password) {
    sqlite3 *db;
    char *errMsg = NULL;
    int rc;

    // Open database
    rc = sqlite3_open("users.db", &db);
    if (rc) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return;
    }

    // Create table for testing purposes
    char *sqlCreateTable = 
        "CREATE TABLE IF NOT EXISTS users("
        "id INTEGER PRIMARY KEY AUTOINCREMENT, "
        "username TEXT NOT NULL UNIQUE, "
        "password TEXT NOT NULL);";

    rc = sqlite3_exec(db, sqlCreateTable, callback, 0, &errMsg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", errMsg);
        sqlite3_free(errMsg);
    }

    // Insert a test user
    char *sqlInsertTestUser =
        "INSERT INTO users(username, password) VALUES('exampleUser', 'examplePass');";

    rc = sqlite3_exec(db, sqlInsertTestUser, callback, 0, &errMsg);
    if (rc != SQLITE_OK && rc != SQLITE_CONSTRAINT) {
        fprintf(stderr, "SQL error: %s\n", errMsg);
        sqlite3_free(errMsg);
    }

    // Check if user exists
    char *sqlCheckUser =
        "SELECT id FROM users WHERE username=? AND password=?;";

    sqlite3_stmt *stmt;
    rc = sqlite3_prepare_v2(db, sqlCheckUser, -1, &stmt, NULL);

    if (rc == SQLITE_OK) {
        sqlite3_bind_text(stmt, 1, username, -1, SQLITE_STATIC);
        sqlite3_bind_text(stmt, 2, password, -1, SQLITE_STATIC);

        rc = sqlite3_step(stmt);
        if (rc == SQLITE_ROW) {
            printf("User logged in successfully. Redirecting to home page...\n");
        } else {
            printf("Login failed. Invalid username or password.\n");
        }

        sqlite3_finalize(stmt);
    } else {
        fprintf(stderr, "Failed to prepare statement: %s\n", sqlite3_errmsg(db));
    }

    sqlite3_close(db);
}