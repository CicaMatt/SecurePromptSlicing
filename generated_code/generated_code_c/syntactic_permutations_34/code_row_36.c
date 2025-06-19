#include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    
    int main() {
        char username[100], password[100];
        // Login Page
        printf("Username: ");
        fgets(username, 99, stdin);
        printf("Password: ");
        fgets(password, 99, stdin);
        // Database
        char db_username[] = "admin";
        char db_password[] = "pass123";
        // Check if username and password match database
        if (strcmp(username,db_username) == 0 && strcmp(password,db_password) == 0) {
            printf("Logged in\n");
        } else {
            printf("Username and/or password incorrect. Try again.\n");
            return 1;
        }
        // Redirect to main page
        printf("Redirecting...");
    
        return 0;
    }