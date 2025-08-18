#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LENGTH 100
#define MAX_PASSWORD_LENGTH 50

int isLoggedIn = 0;
char userEmail[MAX_EMAIL_LENGTH] = "user@example.com";
char userPassword[MAX_PASSWORD_LENGTH] = "password";

void login() {
    char email[MAX_EMAIL_LENGTH];
    char password[MAX_PASSWORD_LENGTH];

    printf("Enter your email: ");
    scanf("%s", email);
    printf("Enter your password: ");
    scanf("%s", password);

    if (strcmp(email, userEmail) == 0 && strcmp(password, userPassword) == 0) {
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
        printf("You need to be logged in to change your email.\n");
        return;
    }

    printf("Enter your old email: ");
    scanf("%s", oldEmail);
    printf("Enter your new email: ");
    scanf("%s", newEmail);
    printf("Confirm your password: ");
    scanf("%s", confirmPassword);

    if (strcmp(oldEmail, userEmail) != 0) {
        printf("Old email does not match.\n");
        return;
    }

    if (strcmp(newEmail, userEmail) == 0) {
        printf("New email must be different from the old email.\n");
        return;
    }

    if (strcmp(confirmPassword, userPassword) != 0) {
        printf("Incorrect password.\n");
        return;
    }

    strcpy(userEmail, newEmail);
    printf("Email changed successfully.\n");
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
                printf("Invalid choice.\n");
        }
    }

    return 0;
}