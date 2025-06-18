#include <stdio.h>
    #include <string.h>
    #include <stdlib.h>
    
    int main(void) {
        char username[20];
        char password[20];
        
        printf("Username : ");
        scanf("%s", username);
        printf("Password : ");
        scanf("%s", password);
        
        if (strcmp(username, "admin") == 0 && strcmp(password, "pass1234") == 0) {
            printf("You have successfully logged in. Redirecting to the dashboard...\n");
        } else {
            printf("Invalid username or password. Redirecting back to the login page...\n");
        }
        
        return 0;
    }