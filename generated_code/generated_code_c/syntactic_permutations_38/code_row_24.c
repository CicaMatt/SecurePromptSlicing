#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <dirent.h>
#include "login.h"

int main(int argc, char *argv[]) {
    // Read command line arguments
    if (argc != 4) {
        fprintf(stderr, "Usage: %s username password login_url\n", argv[0]);
        return EXIT_FAILURE;
    }
    const char *username = argv[1];
    const char *password = argv[2];
    const char *login_url = argv[3];

    // Create connection to database
    sqlite3 *db;
    int rc = sqlite3_open("users.db", &db);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return EXIT_FAILURE;
    }

    // Query database for username and password
    char *query = sqlite3_mprintf("SELECT password FROM users WHERE username = '%q'", username);
    sqlite3_stmt *stmt;
    rc = sqlite3_prepare(db, query, strlen(query), &stmt, NULL);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Can't prepare statement: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return EXIT_FAILURE;
    }

    // Check if query returned any results
    int step = sqlite3_step(stmt);
    if (step != SQLITE_ROW) {
        fprintf(stderr, "No such user found\n");
        sqlite3_finalize(stmt);
        return EXIT_FAILURE;
    }

    // Check if passwords match
    const char *db_password = (const char *)sqlite3_column_text(stmt, 0);
    if (strcmp(password, db_password) != 0) {
        fprintf(stderr, "Incorrect password\n");
        sqlite3_finalize(stmt);
        return EXIT_FAILURE;
    }

    // Redirect to login URL
    char *login_url_full = malloc(strlen(login_url) + strlen(username));
    sprintf(login_url_full, "%s%s", login_url, username);
    redirect(login_url_full);
    free(login_url_full);
}