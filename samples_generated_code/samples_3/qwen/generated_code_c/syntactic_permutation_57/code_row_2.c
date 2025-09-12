#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LENGTH 100
#define MAX_PASSWORD_LENGTH 50

int isLoggedIn = 0;
char userEmail[MAX_EMAIL_LENGTH];
char userPassword[MAX_PASSWORD_LENGTH];

void login() {
    printf("Enter your email: ");
    scanf("%s", userEmail);
    printf("Enter your password: ");
    scanf("%s", userPassword);
    isLoggedIn = 1; // For demonstration purposes, assume login is always successful
}

int verifyUser(const char* oldEmail, const char* confirmPassword) {
    return strcmp(userEmail, oldEmail) == 0 && strcmp(userPassword, confirmPassword) == 0;
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
    printf("Enter your new email: ");
    scanf("%s", newEmail);
    printf("Confirm your password: ");
    scanf("%s", confirmPassword);

    if (verifyUser(oldEmail, confirmPassword)) {
        strcpy(userEmail, newEmail);
        printf("Email changed successfully.\n");
    } else {
        printf("Incorrect old email or password. Email change failed.\n");
    }
}

int main() {
    int choice;

    while (1) {
        printf("\n1. Login\n2. Change Email\n3. Exit\n");
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