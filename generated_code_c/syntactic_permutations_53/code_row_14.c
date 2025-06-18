#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include "sqlite3.h"
#define MAX_DATA 1024

char *username;
char *password;
int admin = 0;

void logIn(char *usr, char *pwd) {
    username = usr;
    password = pwd;
}

void isLoggedIn() {
    if (strlen(username) > 0 && strlen(password) > 0) {
        return;
    }
    else{
        printf("You are not logged in.");
        exit(1);
    }
}

int main(void) {
    logIn("admin", "password");
    isLoggedIn();
    
    int rc, i, idx;
    sqlite3 *db;
    char *err_msg = 0;
    char sql[50];
    int userID;
    
    /* Open database */
    rc = sqlite3_open("login.db", &db);
    if (rc) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
    }
    
    /* Create SQL statement */
    sprintf(sql, "SELECT * FROM users WHERE username = '%s' AND password = '%s'", username, password);
    
    /* Execute SQL statement */
    rc = sqlite3_exec(db, sql, callback, 0, &err_msg);
    if (rc != SQLITE_OK ) {
        fprintf(stderr, "SQL error: %s\n", err_msg);
    }
    
    /* Print */
    for(i=0; i<userID; i++) {
        printf("%d ", userID[i]);
    }
    printf("\n");
    
    return 0;
}

int callback(void *NotUsed, int argc, char **argv, char **azColName) {
    if (admin == 1) {
        printf("You are an admin.");
    }
    else{
        printf("You are not an admin.");
    }
}