#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sql-connector.h"

int login_function(const char *username, const char *password) {
    /* Connect to the database */
    sql_connect();
    
    /* Query the database if username exists */
    int user_exists = sql_query("SELECT COUNT(*) FROM users WHERE username='%s'", username);
    
    /* If the username doesn't exist return 0 (authentication failed) */
    if (!user_exists) {
        return 0;
    }
    
    /* Get the hashed password from database */
    char *hashed_password = sql_query("SELECT password FROM users WHERE username='%s'", username);
    
    /* If the password is incorrect return 0 (authentication failed)*/
    if (strcmp(hashed_password, password)) {
        free(hashed_password);
        return 0;
    }
    
    /* Authentication is successful */
    free(hashed_password);
    return 1;
}