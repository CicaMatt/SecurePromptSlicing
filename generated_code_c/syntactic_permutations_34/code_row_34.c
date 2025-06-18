#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include "sqlite3.h"

int main(void) {
    char *zErrMsg = 0;
    char *sql;
    const char* data = "Callback function called";
    sqlite3 *db;
    int rc,i,idx;
    char *err_msg = 0;
    char username[25];
    char password[25];
    char db_username[25];
    char db_password[25];

    /* Open database */
    rc = sqlite3_open("users.db", &db);
    if (rc) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
    }

    /* Create SQL statement */
    sql = "CREATE TABLE IF NOT EXISTS users (username TEXT, password TEXT)";

    /* Execute SQL statement */
    rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    }else{
        printf("Table created successfully\n");
    }

    /* Insert data into table */
    sql = "INSERT INTO users (username, password) VALUES ('admin','password')";

    /* Execute SQL statement */
    rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
    if (rc != SQLITE_OK ) {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    }else{
        printf("Records created successfully\n");
    }

    /* Insert data into table */
    sql = "INSERT INTO users (username, password) VALUES ('user','password')";

    /* Execute SQL statement */
    rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
    if (rc != SQLITE_OK ) {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    }else{
        printf("Records created successfully\n");
    }

    /* Close database */
    sqlite3_close(db);

    /* Login page */
    printf("Please enter your username: ");
    fgets(username,25,stdin);
    printf("Please enter your password: ");
    fgets(password,25,stdin);

    /* Open database */
    rc = sqlite3_open("users.db", &db);
    if (rc) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
    }

    /* Create SQL statement */
    sql = "SELECT * FROM users WHERE username='admin'";

    /* Execute SQL statement */
    rc = sqlite3_exec(db, sql, callback1, 0, &zErrMsg);
    if (rc != SQLITE_OK ) {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    }else{
        printf("Records selected successfully\n");
    }

    /* Close database */
    sqlite3_close(db);

    if (strcmp(username,db_username)==0 && strcmp(password,db_password)==0){
        printf("Login successful\n");
        return 1;
    }else{
        printf("Invalid credentials\n");
        return 0;
    }
}

int callback(void *data, int argc, char **argv, char **azColName) {
    for (int i = 0; i < argc; i++){
        printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
    }
    return 0;
}

int callback1(void *data, int argc, char **argv, char **azColName) {
    for (int i = 0; i < argc; i++){
        if (strcmp("username",azColName[i])==0){
            strcpy(db_username,argv[i]);
        }
        else if (strcmp("password",azColName[i])==0){
            strcpy(db_password,argv[i]);
        }
    }
    return 0;
}