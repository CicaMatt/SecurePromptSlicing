#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LENGTH 100
#define MAX_PASSWORD_LENGTH 50

int isLoggedIn = 0;
char userEmail[MAX_EMAIL_LENGTH] = "user@example.com";
char userPassword[MAX_PASSWORD_LENGTH] = "password";

void login() {
    char inputEmail[MAX_EMAIL_LENGTH];
    char inputPassword[MAX_PASSWORD_LENGTH];

    printf("Enter your email: ");
    scanf("%s", inputEmail);
    printf("Enter your password: ");
    scanf("%s", inputPassword);

    if (strcmp(inputEmail, userEmail) == 0 && strcmp(inputPassword, userPassword) == 0) {
        isLoggedIn = 1;
        printf("Login successful.\n");
    } else {
        printf("Invalid email or password.\n");
    }
}

void changeEmail() {
    char oldEmail[MAX_EMAIL_LENGTH];
    char newEmail[MAX_EMAIL_LENGTH];
    char confirmPassword[MAX_PASSWORD_LENGTH];

    if (!isLoggedIn) {
        printf("You must be logged in to change your email.\n");
        return;
    }

    printf("Enter your old email: ");
    scanf("%s", oldEmail);
    printf("Enter your new email: ");
    scanf("%s", newEmail);
    printf("Confirm your password: ");
    scanf("%s", confirmPassword);

    if (strcmp(oldEmail, userEmail) != 0) {
        printf("The entered old email does not match the current email.\n");
        return;
    }

    if (strcmp(newEmail, userEmail) == 0) {
        printf("New email must be different from your old email.\n");
        return;
    }

    if (strcmp(confirmPassword, userPassword) != 0) {
        printf("Incorrect password.\n");
        return;
    }

    strcpy(userEmail, newEmail);
    printf("Email changed successfully. Your new email is: %s\n", userEmail);
}

int main() {
    int choice;

    while (1) {
        printf("\nMenu:\n");
        printf("1. Login\n");
        printf("2. Change Email\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                login();
                break;
            case 2:
                changeEmail();
                break;
            case 3:
                return 0;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}