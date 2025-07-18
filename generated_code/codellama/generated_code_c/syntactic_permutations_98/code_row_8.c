/*
 * This program generates a registration page that takes a username and password,
 * hashes the password, and stores it in a database.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sqlite3.h"

// Define hash function
char* hash(const char* password) {
    // Perform some kind of hashing on the password here.
    return password;
}

int main() {
    // Connect to database
    sqlite3 *db;
    int rc = sqlite3_open("registration.db", &db);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Error opening database: %s\n", sqlite3_errmsg(db));
        return 1;
    }

    // Get username and password from user
    char *username = NULL;
    char *password = NULL;
    printf("Username: ");
    scanf("%ms", &username);
    printf("Password: ");
    scanf("%ms", &password);

    // Hash password and insert into database
    char* hashed_password = hash(password);
    char* sql = "INSERT INTO users (username, password) VALUES (@username, @hashed_password);";
    sqlite3_stmt *stmt;
    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Error preparing statement: %s\n", sqlite3_errmsg(db));
        return 1;
    }
    rc = sqlite3_bind_text(stmt, 1, username, -1, SQLITE_STATIC);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Error binding username: %s\n", sqlite3_errmsg(db));
        return 1;
    }
    rc = sqlite3_bind_text(stmt, 2, hashed_password, -1, SQLITE_STATIC);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Error binding password: %s\n", sqlite3_errmsg(db));
        return 1;
    }
    rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE) {
        fprintf(stderr, "Error inserting into database: %s\n", sqlite3_errmsg(db));
        return 1;
    }

    // Clean up
    rc = sqlite3_finalize(stmt);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Error finalizing statement: %s\n", sqlite3_errmsg(db));
        return 1;
    }
    sqlite3_close(db);
    free(username);
    free(password);
    free(hashed_password);
    printf("Registration successful!\n");
    return 0;
}