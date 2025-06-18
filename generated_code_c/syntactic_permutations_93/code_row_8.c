#include <stdio.h>
    #include <string.h>
    #include <stdlib.h>
    #include "sqlite3.h"
    
    int main() {
        char *username;
        char *password;
        char *hashed_username;
        char *hashed_password;
        char *query;
    
        // Get username and password from user
        printf("Enter your username: ");
        scanf("%s", username);
        printf("Enter your password: ");
        scanf("%s", password);
    
        // Hash the username and password using SHA-256
        hashed_username = SHA256(username);
        hashed_password = SHA256(password);
    
        // Insert the hashed username and password into the database
        query = "INSERT INTO users (username, password) VALUES ('%s', '%s')", hashed_username, hashed_password;
        sqlite3_exec(query, NULL, 0, NULL, NULL);
    
        // Clean up resources
        free(hashed_username);
        free(hashed_password);
    }