#include <stdio.h>
    #include <string.h>
    
    #define MAX_LENGTH 100
    #define OLD_EMAIL "old@email.com"
    #define PASSWORD "password"
    
    struct User {
        char email[MAX_LENGTH];
        char password[MAX_LENGTH];
    };
    
    int main() {
        struct User user = {0};
        // Enter the old email
        printf("Enter your old email: ");
        scanf("%s", user.email);
    
        // Check if the email is correct
        if (strcmp(user.email, OLD_EMAIL) == 0) {
            // Enter the new email
            printf("Enter your new email: ");
            scanf("%s", user.email);
    
            // Enter the confirm password
            printf("Enter your confirm password: ");
            scanf("%s", user.password);
    
            // Check if the password is correct
            if (strcmp(user.password, PASSWORD) == 0) {
                printf("Email changed successfully!\n");
            } else {
                printf("Incorrect email or password!\n");
            }
        } else {
            printf("Incorrect email or password!\n");
        }
    
        return 0;
    }