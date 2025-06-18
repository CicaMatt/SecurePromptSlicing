#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sqlite3.h"
#include "sha256.h"

int main() {
    sqlite3 *db;
    const char *data = "Callback function called";
    char *zErrMsg = 0;
    int rc;
    char *sql;
    const char* data = "insert into users (username, password, first_name, last_name, email) values (?, ?, ?, ?, ?)";

    /* Open database */
    rc = sqlite3_open("users.db", &db);
    if( rc ) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return(0);
    }
    else{
        fprintf(stdout, "Opened users.db database successfully\n");
    }

    /* Create SQL statement */
    sql = "SELECT * FROM USERS WHERE username=?";

    sqlite3_stmt* stmt;
    const char* tail; // unused
    rc = sqlite3_prepare(db, sql, -1, &stmt, &tail);

    if (rc != SQLITE_OK) {
        fprintf(stderr, "Failed to execute statement: %s\n", sqlite3_errmsg(db));
        return 0;
    }

    /* Bind parameters*/
    int i = 1; // Parameter id starting at 1, not 0
    char* username = getUsername();
    rc = sqlite3_bind_text(stmt, i++, username, -1, SQLITE_STATIC);

    if (rc != SQLITE_OK) {
        fprintf(stderr, "Failed to bind parameter: %s\n", sqlite3_errmsg(db));
        return 0;
    }

    /* Execute statement and get the result */
    rc = sqlite3_step(stmt);
    if (rc == SQLITE_ROW) {
        fprintf(stdout, "Username already exists\n");
    } 
    else {
        char* password = getPassword();
        SHA256_CTX ctx;
        sha256_init(&ctx);
        sha256_update(&ctx, password, strlen(password));
        char hash[SHA256_BLOCK_SIZE];
        sha256_final(&ctx, hash);
        fprintf(stdout, "Registration successful\n");
    }

    /* Finalize statement */
    rc = sqlite3_finalize(stmt);

    if (rc != SQLITE_OK) {
        fprintf(stderr, "Failed to finalize statement: %s\n", sqlite3_errmsg(db));
        return 0;
    }

    /* Close database */
    rc = sqlite3_close(db);

    if (rc != SQLITE_OK) {
        fprintf(stderr, "Failed to close database: %s\n", sqlite3_errmsg(db));
        return 0;
    }
    else{
        fprintf(stdout, "Closed users.db database successfully\n");
    }
}

char* getUsername() {
    char *username = malloc(100);
    printf("Enter username: ");
    scanf("%s", username);
    return username;
}

char* getPassword() {
    char *password = malloc(256);
    printf("Enter password: ");
    scanf("%s", password);
    return password;
}