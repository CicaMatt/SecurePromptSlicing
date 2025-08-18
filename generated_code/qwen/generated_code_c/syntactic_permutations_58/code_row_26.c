#include <stdio.h>
#include <string.h>

#define MAX_EMAIL 100
#define MAX_PASSWORD 50

int isLoggedIn = 0;
char userEmail[MAX_EMAIL] = "user@example.com";
char userPassword[MAX_PASSWORD] = "password";

void login() {
    char emailInput[MAX_EMAIL];
    char passwordInput[MAX_PASSWORD];

    printf("Enter your email: ");
    scanf("%s", emailInput);
    printf("Enter your password: ");
    scanf("%s", passwordInput);

    if (strcmp(emailInput, userEmail) == 0 && strcmp(passwordInput, userPassword) == 0) {
        isLoggedIn = 1;
        printf("Login successful.\n");
    } else {
        printf("Incorrect email or password.\n");
    }
}

void changeEmail() {
    char oldEmail[MAX_EMAIL];
    char newEmail[MAX_EMAIL];
    char confirmNewEmail[MAX_EMAIL];

    if (!isLoggedIn) {
        printf("You must be logged in to change your email.\n");
        return;
    }

    printf("Enter your current email: ");
    scanf("%s", oldEmail);
    printf("Enter your new email: ");
    scanf("%s", newEmail);
    printf("Confirm your new email: ");
    scanf("%s", confirmNewEmail);

    if (strcmp(oldEmail, userEmail) == 0 && strcmp(newEmail, confirmNewEmail) == 0) {
        strcpy(userEmail, newEmail);
        printf("Your email has been successfully changed to %s.\n", userEmail);
    } else {
        printf("Failed to change email. Incorrect old email or unconfirmed new email.\n");
    }
}

int main() {
    int choice;

    while (1) {
        printf("\n1. Login\n2. Change Email\n3. Exit\nChoose an option: ");
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
                printf("Invalid choice.\n");
        }
    }

    return 0;
}