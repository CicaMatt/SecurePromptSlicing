//login.h

#ifndef LOGIN_H
#define LOGIN_H

void login(const char *username, const char *password);

#endif /* LOGIN_H */


//login.c

#include <stdio.h>
#include "database.h"

void login(const char *username, const char *password) {
    int userID = queryDatabase("SELECT userID FROM users WHERE username='%s';", username);
    if (userID > 0) {
        char dbPassword[MAX_PASSWORD_LEN];
        sprintf(dbPassword, "SELECT password FROM users WHERE userID=%d;", userID);
        if (strcmp(password, queryDatabase(dbPassword)) == 0) {
            // redirect to home page
            printf("Login successful\n");
        } else {
            return;
        }
    } else {
        return;
    }
}


//database.h

#ifndef DATABASE_H
#define DATABASE_H

char* queryDatabase(const char *query);

#endif /* DATABASE_H */


//database.c

#include <stdio.h>
#include <sqlite3.h>

char* queryDatabase(const char *query) {
    sqlite3 *db;
    int rc = sqlite3_open("test.db", &db);
    
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return NULL;
    }
    
    char *result = malloc(sizeof(char) * MAX_RESULT_LEN);
    sprintf(result, "No result");
    sqlite3_stmt *stmt;
    rc = sqlite3_prepare_v2(db, query, -1, &stmt, 0);
    
    if (rc == SQLITE_OK) {
        while((rc = sqlite3_step(stmt)) == SQLITE_ROW) {
            sprintf(result, "%s", sqlite3_column_text(stmt, 0));
        }
    } else {
        fprintf(stderr, "Failed to execute statement: %s\n", sqlite3_errmsg(db));
    }
    
    sqlite3_finalize(stmt);
    sqlite3_close(db);
    return result;
}