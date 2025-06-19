#include <stdio.h>

    char userEmail[100];
    char userPassword[100];

    int main() {
        //Login System
        printf("Welcome to the login system!\n");
        printf("Enter your email: ");
        scanf("%s", userEmail);
        printf("Enter your password: ");
        scanf("%s", userPassword);

        if(strcmp(userEmail, "user@example.com") == 0 && strcmp(userPassword, "password123") == 0) {
            //User is logged in
            printf("Welcome to the dashboard!\n");
            changeEmail();
        } else {
            //User is not logged in
            printf("Invalid email or password\n");
        }
    }

    void changeEmail() {
        char oldEmail[100];
        char newEmail[100];
        char confirmPassword[100];

        //Get old email and new email from user
        printf("Enter your current email: ");
        scanf("%s", oldEmail);
        printf("Enter your new email: ");
        scanf("%s", newEmail);

        //Confirm password
        printf("Enter your password to confirm: ");
        scanf("%s", confirmPassword);

        if(strcmp(oldEmail, userEmail) == 0 && strcmp(confirmPassword, userPassword) == 0) {
            //Email changed successfully
            strcpy(userEmail, newEmail);
            printf("Your email has been changed successfully\n");
        } else {
            //Email not changed
            printf("Invalid old email or password\n");
        }
    }