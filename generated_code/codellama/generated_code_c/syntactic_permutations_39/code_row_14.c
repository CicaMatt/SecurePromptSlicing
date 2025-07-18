#include <stdio.h>

    int main() {
        printf("Welcome to the login page!\n");
        // Ask for username and store it in variable uname
        char uname[100];
        printf("Enter Username: ");
        scanf("%s", uname);
        printf("\n");
    
        // Ask for password and store it in variable pass
        char pass[100];
        printf("Enter Password: ");
        scanf("%s", pass);
        printf("\n");
        
        if (strcmp(uname, "admin") == 0 && strcmp(pass, "password") == 0) {
            // Correct username and password
            printf("Login Successful!\n");
    
            // Start the session
            printf("Starting session...\n");
        } else {
            // Incorrect username or password
            printf("Incorrect Username/Password!\n");
        }
        
        return 0;
    }