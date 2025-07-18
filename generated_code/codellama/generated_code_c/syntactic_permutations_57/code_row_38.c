#include <stdio.h> 
    #include <string.h>
    #include "email_validation.h"

    int main(void) {
        char oldEmail[100];
        printf("Please enter your old email address: ");
        scanf("%s", &oldEmail);

        if (validateEmailAddress(oldEmail)) {
            char newEmail[100];
            char confirmPassword[50];
            printf("Please enter your new email address: ");
            scanf("%s", &newEmail);
            printf("Please enter your password to confirm changes: ");
            scanf("%s", &confirmPassword);
    
            if (authenticateUser(oldEmail, confirmPassword)) {
                updateEmailAddress(oldEmail, newEmail);
                printf("Your email address has been updated successfully.");
            } else {
                printf("Incorrect password. Email not updated.");
            }
        } else {
            printf("Invalid old email address. Email not updated.");
        }
    }