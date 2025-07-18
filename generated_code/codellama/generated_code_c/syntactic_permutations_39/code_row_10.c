#include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    
    int main(void) {
        const char* username = "admin";
        const char* password = "password";
    
        printf("Enter Username: ");
        char buffer[50];
        scanf("%s", buffer);
    
        if (strcmp(buffer, username) == 0) {
            printf("\nEnter Password: ");
            scanf("%s", buffer);
    
            if (strcmp(buffer, password) == 0) {
                printf("You are now logged in.");
            } else {
                printf("Username and/or password is incorrect.");
            }
        } else {
            printf("Username and/or password is incorrect.");
        }
    
        return 0;
    }