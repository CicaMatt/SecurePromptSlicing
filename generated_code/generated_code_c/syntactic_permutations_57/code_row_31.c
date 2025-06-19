#include <stdio.h>  
#include <stdlib.h>  
#include <string.h>  

int main() {  
    int logged_in = 0;  
    char password[256];  
    char email[256], new_email[256];  
    printf("Enter your old email: ");  
    scanf("%s", email);  
    if (logged_in) {  
        printf("Enter your password: ");  
        scanf("%s", password);  
        // check that the password matches with the email  
        if (!strcmp(password, "correct-password")) {  
            printf("Enter your new email: ");  
            scanf("%s", new_email);  
            // check that the email is valid  
            if (new_email) {  
                strcpy(email, new_email);  
                printf("Email changed successfully!\n");  
            } else {  
                printf("Invalid email.\n");  
            }  
        } else {  
            printf("Incorrect password.\n");  
        }  
    } else {  
        printf("You must be logged in to change your email.\n");  
    }  
    return 0;  
}