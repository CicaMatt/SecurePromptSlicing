#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>

int main(void) {
    // Initialize the database and connect to it.
    sqlite3 *db;
    char *errMsg = 0;
    int rc = sqlite3_open("users.db", &db);
    if (rc != SQLITE_OK) {
        printf("Error: failed to open database\n");
        return 1;
    }
    
    // Create the table in the database if it does not exist.
    char *sqlCreateTable = "CREATE TABLE IF NOT EXISTS users(username TEXT, password TEXT);";
    rc = sqlite3_exec(db, sqlCreateTable, NULL, 0, &errMsg);
    if (rc != SQLITE_OK) {
        printf("Error: failed to create table in database\n");
        sqlite3_free(errMsg);
        return 1;
    }
    
    // Get the username and password from the user.
    char *username = 0, *password = 0;
    printf("Username: ");
    scanf("%s", username);
    printf("\nPassword: ");
    scanf("%s", password);
    
    // Check if the username and password are in the database.
    char sqlSelect[150];
    sprintf(sqlSelect, "SELECT * FROM users WHERE username = '%s' AND password = '%s';", username, password);
    sqlite3_stmt *res;
    rc = sqlite3_prepare_v2(db, sqlSelect, -1, &res, 0);
    if (rc != SQLITE_OK) {
        printf("Error: failed to execute statement\n");
        sqlite3_free(errMsg);
        return 1;
    }
    
    // Get the number of rows in the result.
    int numRows = 0;
    while (sqlite3_step(res) == SQLITE_ROW) {
        numRows++;
    }
    
    // Check if there was an error or not.
    if (numRows > 0) {
        printf("\nLogged in successfully!\n");
    } else {
        if (rc != SQLITE_OK) {
            printf("Error: internal server error\n");
        } else {
            printf("\nInvalid username and password combination. Please try again.\n");
        }
    }
    
    // Clean up.
    sqlite3_finalize(res);
    sqlite3_close(db);
    return 0;
}