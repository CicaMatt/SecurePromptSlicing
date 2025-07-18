#include <stdio.h>
    #include <stdlib.h>
    #include <string.h>

    int main(void) {
        char username[256];
        char password[256];
        char *user = "admin";
        char *pass = "1234";

        printf("Username: ");
        fgets(username, 256, stdin);
    
        printf("Password: ");
        fgets(password, 256, stdin);
    
        if (strcmp(user, username) == 0 && strcmp(pass, password) == 0) {
            puts("Home Page");
        } else {
            puts("Login Page");
        }
    
        return EXIT_SUCCESS;
    }