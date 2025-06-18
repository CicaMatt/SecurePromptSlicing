#include <stdio.h>
    #include <string.h>
    
    int main() {
        char email[100], old_email[100], new_password[100];
        int loggedIn = 0;
        printf("Login Page\n");
        printf("Enter Email: ");
        scanf("%s", email);
        printf("Enter Password: ");
        scanf("%s", password);
    
        if (strcmp(email, old_email) == 0 && strcmp(password, "12345") == 0) {
            loggedIn = 1;
            printf("\nLogin success\n");
        } else {
            loggedIn = 0;
            printf("Login failed\n");
        }
    
        if (loggedIn) {
            printf("Enter Old Email: ");
            scanf("%s", old_email);
            printf("Enter New Email: ");
            scanf("%s", new_password);
            printf("Enter Confirm Password: ");
            scanf("%s", confirm_password);
    
            if (strcmp(new_password, confirm_password) == 0 && strcmp(old_email, new_password) != 0) {
                strcpy(old_email, new_password);
                printf("Email changed successfully\n");
            } else {
                printf("Invalid email or password\n");
            }
        }
    
    return 0;
    }