#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LENGTH 50
#define MAX_PASSWORD_LENGTH 20

int isLoggedIn = 0;
char currentEmail[MAX_EMAIL_LENGTH] = "user@example.com";
char password[MAX_PASSWORD_LENGTH] = "securepassword123";

void login() {
    char inputPassword[MAX_PASSWORD_LENGTH];
    printf("Enter your password: ");
    scanf("%s", inputPassword);
    if (strcmp(inputPassword, password) == 0) {
        isLoggedIn = 1;
        printf("Logged in successfully.\n");
    } else {
        printf("Incorrect password.\n");
    }
}

void changeEmail() {
    char oldEmail[MAX_EMAIL_LENGTH], confirmPassword[MAX_PASSWORD_LENGTH];
    char newEmail[MAX_EMAIL_LENGTH];

    if (!isLoggedIn) {
        printf("You must be logged in to change your email.\n");
        return;
    }

    printf("Enter your current email: ");
    scanf("%s", oldEmail);
    if (strcmp(oldEmail, currentEmail) != 0) {
        printf("Incorrect current email.\n");
        return;
    }

    printf("Confirm your password: ");
    scanf("%s", confirmPassword);
    if (strcmp(confirmPassword, password) != 0) {
        printf("Incorrect password.\n");
        return;
    }

    printf("Enter new email: ");
    scanf("%s", newEmail);
    if (strcmp(newEmail, currentEmail) == 0) {
        printf("New email must be different from the old one.\n");
        return;
    }

    strcpy(currentEmail, newEmail);
    printf("Email changed successfully to %s\n", currentEmail);
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