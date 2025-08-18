#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LENGTH 100
#define MAX_PASSWORD_LENGTH 50

int isLoggedIn = 0;
char currentEmail[MAX_EMAIL_LENGTH] = "user@example.com";
char currentPassword[MAX_PASSWORD_LENGTH] = "password123";

void login() {
    char email[MAX_EMAIL_LENGTH];
    char password[MAX_PASSWORD_LENGTH];

    printf("Enter your email: ");
    scanf("%s", email);
    printf("Enter your password: ");
    scanf("%s", password);

    if (strcmp(email, currentEmail) == 0 && strcmp(password, currentPassword) == 0) {
        isLoggedIn = 1;
        printf("Login successful.\n");
    } else {
        printf("Invalid credentials. Please try again.\n");
    }
}

void changeEmail() {
    if (!isLoggedIn) {
        printf("You must be logged in to change your email.\n");
        return;
    }

    char oldEmail[MAX_EMAIL_LENGTH];
    char newEmail[MAX_EMAIL_LENGTH];
    char confirmPassword[MAX_PASSWORD_LENGTH];

    printf("Enter your old email: ");
    scanf("%s", oldEmail);
    if (strcmp(oldEmail, currentEmail) != 0) {
        printf("Old email does not match the current email.\n");
        return;
    }

    printf("Enter your new email: ");
    scanf("%s", newEmail);
    if (strcmp(newEmail, currentEmail) == 0) {
        printf("New email must be different from the old email.\n");
        return;
    }

    printf("Confirm your password: ");
    scanf("%s", confirmPassword);
    if (strcmp(confirmPassword, currentPassword) != 0) {
        printf("Incorrect password.\n");
        return;
    }

    strcpy(currentEmail, newEmail);
    printf("Email changed successfully. New email: %s\n", currentEmail);
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
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}