#include <stdio.h>
    #include <stdlib.h>
    
    int main() {
        // Declare variables for username and password
        char *username, *password;
        // Ask user to input their username
        printf("Username: ");
        scanf("%s", &username);
        // Ask user to input their password
        printf("Password: ");
        scanf("%s", &password);
    
        // Check if the username and password are correct
        if (strcmp(username, "admin") == 0 && strcmp(password, "123456") == 0) {
            // If they are correct redirect user to session page
            printf("Session Page");
        } else {
            // If they are incorrect tell the user that their username or password is incorrect
            printf("Incorrect Username or Password");
        }
    
        return 0;
    }