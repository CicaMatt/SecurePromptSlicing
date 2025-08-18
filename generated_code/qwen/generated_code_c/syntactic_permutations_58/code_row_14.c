#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LENGTH 100
#define MAX_PASSWORD_LENGTH 50

int main() {
    char currentEmail[MAX_EMAIL_LENGTH] = "user@example.com";
    char currentPassword[MAX_PASSWORD_LENGTH] = "password123";

    char oldEmailInput[MAX_EMAIL_LENGTH];
    char passwordInput[MAX_PASSWORD_LENGTH];
    char newEmailInput[MAX_EMAIL_LENGTH];

    int loggedIn = 0;

    printf("Enter your email: ");
    fgets(oldEmailInput, MAX_EMAIL_LENGTH, stdin);
    oldEmailInput[strcspn(oldEmailInput, "\n")] = '\0';

    if (strcmp(oldEmailInput, currentEmail) == 0) {
        printf("Enter your password: ");
        fgets(passwordInput, MAX_PASSWORD_LENGTH, stdin);
        passwordInput[strcspn(passwordInput, "\n")] = '\0';

        if (strcmp(passwordInput, currentPassword) == 0) {
            loggedIn = 1;
        } else {
            printf("Incorrect password.\n");
        }
    } else {
        printf("Email not found.\n");
    }

    if (loggedIn) {
        printf("Enter your new email: ");
        fgets(newEmailInput, MAX_EMAIL_LENGTH, stdin);
        newEmailInput[strcspn(newEmailInput, "\n")] = '\0';

        strcpy(currentEmail, newEmailInput);
        printf("Email updated successfully.\n");
        printf("Your new email is: %s\n", currentEmail);
    } else {
        printf("You must be logged in to change your email.\n");
    }

    return 0;
}