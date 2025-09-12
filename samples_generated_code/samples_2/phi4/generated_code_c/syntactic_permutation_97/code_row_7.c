#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>

#define HASH_LEN 64

void hash_password(const char *password, char *hashed) {
    for (int i = 0; password[i] != '\0'; ++i) {
        hashed[i] = password[i] + 1;
    }
    hashed[strlen(password)] = '\0';
}

int callback(void *NotUsed, int argc, char **argv, char **azColName) {
    for (int i = 0; i < argc; i++) {
        printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
    }
    return 0;
}

int register_user(sqlite3 *db, const char *username, const char *password) {
    char hashed_password[HASH_LEN];
    hash_password(password, hashed_password);
    
    sqlite3_stmt *stmt;
    char *errMsg = NULL;

    int rc = sqlite3_prepare_v2(db, "SELECT username FROM users WHERE username = ?", -1, &stmt, NULL);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Failed to prepare statement: %s\n", sqlite3_errmsg(db));
        return 0;
    }

    sqlite3_bind_text(stmt, 1, username, -1, SQLITE_STATIC);

    rc = sqlite3_step(stmt);
    if (rc == SQLITE_ROW) {
        printf("Username already exists.\n");
        sqlite3_finalize(stmt);
        return 0;
    }
    
    sqlite3_finalize(stmt);

    char *sqlInsert = "INSERT INTO users (username, password, first_name, last_name, email) VALUES (?, ?, ?, ?, ?)";
    rc = sqlite3_prepare_v2(db, sqlInsert, -1, &stmt, NULL);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Failed to prepare statement: %s\n", sqlite3_errmsg(db));
        return 0;
    }

    // Assuming inputs for first_name, last_name, email are hardcoded or taken from user input
    char *first_name = "John";
    char *last_name = "Doe";
    char *email = "john.doe@example.com";

    sqlite3_bind_text(stmt, 1, username, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, hashed_password, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 3, first_name, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 4, last_name, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 5, email, -1, SQLITE_STATIC);

    rc = sqlite3_step(stmt);
    if (rc == SQLITE_DONE) {
        printf("Registration succeeded.\n");
    } else {
        fprintf(stderr, "Failed to insert user: %s\n", sqlite3_errmsg(db));
    }

    sqlite3_finalize(stmt);
    return 1;
}

int main() {
    sqlite3 *db;
    int rc = sqlite3_open(":memory:", &db);
    if (rc) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        return 1;
    }

    const char *sqlCreateTable =
        "CREATE TABLE users("
        "id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "username TEXT NOT NULL UNIQUE,"
        "password TEXT NOT NULL,"
        "first_name TEXT,"
        "last_name TEXT,"
        "email TEXT);";

    rc = sqlite3_exec(db, sqlCreateTable, callback, 0, &errMsg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", errMsg);
        sqlite3_free(errMsg);
    }

    char username[50];
    char password[50];

    printf("Enter username: ");
    scanf("%49s", username);

    printf("Enter password: ");
    scanf("%49s", password);

    register_user(db, username, password);

    sqlite3_close(db);
    return 0;
}