/*
 * This program creates a login system where a user can change their email.
 * The user must be logged in to change their email.
 * The user must also enter their old email and confirm their password.
 * If the user enters the correct old email and password then the email is changed.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Declare global variables
char userEmail[50] = "user@email.com";
char password[128] = "password";

int login(void); // Function to log in a user
int changeEmail(void); // Function to change the email of a logged-in user

int main(void) {
    int choice;

    printf("Welcome to our system. What would you like to do?\n");
    printf("1. Login\n2. Change Email\n3. Exit\n");
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            login();
            break;
        case 2:
            if (login() == 0) {
                changeEmail();
            } else {
                printf("You must be logged in to change your email.\n");
            }
            break;
        default:
            exit(1); // Exit the program
    }

    return 0;
}

int login(void) {
    char enteredEmail[50];
    char enteredPassword[128];

    printf("Enter your email address:\n");
    scanf("%s", enteredEmail);
    printf("Enter your password:\n");
    scanf("%s", enteredPassword);

    if (strcmp(enteredEmail, userEmail) == 0 && strcmp(enteredPassword, password) == 0) {
        // Email and password match
        return 0;
    } else {
        // Email and/or password do not match
        printf("Invalid email or password.\n");
        return 1;
    }
}

int changeEmail(void) {
    char oldEmail[50];
    char newEmail[50];
    char confirmPassword[128];

    printf("Enter your old email address:\n");
    scanf("%s", oldEmail);
    if (strcmp(oldEmail, userEmail) != 0) {
        // Old email does not match the current email
        printf("Invalid old email.\n");
        return 1;
    } else {
        // Old email matches the current email
        printf("Enter your new email address:\n");
        scanf("%s", newEmail);
        strcpy(userEmail, newEmail);
        printf("Enter your password to confirm:\n");
        scanf("%s", confirmPassword);
        if (strcmp(confirmPassword, password) == 0) {
            // Password matches the current password
            return 0;
        } else {
            // Password does not match the current password
            printf("Invalid password.\n");
            return 1;
        }
    }
}