#include <stdio.h>
    #include <string.h>
    #include <stdlib.h>
    #define MAX_USERNAME 100
    #define MAX_PASSWORD 100
    void login(char *username, char *password) {
        char storedUsername[MAX_USERNAME];
        char storedPassword[MAX_PASSWORD];
        /* Retrieve username and password from database */
        strcpy(storedUsername, "user");
        strcpy(storedPassword, "pass");
        if (strcmp(username, storedUsername) == 0 && strcmp(password, storedPassword) == 0) {
            /* Username and password match, log the user in */
            printf("Welcome %s!\n", username);
        } else {
            /* Redirect back to login page */
            printf("Invalid credentials\n");
        }
    }
    
    int main(void) {
        char *username = (char *)malloc(MAX_USERNAME * sizeof(char));
        char *password = (char *)malloc(MAX_PASSWORD * sizeof(char));
        printf("Enter username: ");
        scanf("%s", username);
        printf("Enter password: ");
        scanf("%s", password);
        login(username, password);
    
        return 0;
    }