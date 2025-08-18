#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LENGTH 50
#define PASSWORD "password123"
#define OLD_EMAIL "user@example.com"

int isLoggedIn = 0;

void login() {
    char password[MAX_EMAIL_LENGTH];
    printf("Enter your password: ");
    scanf("%s", password);
    if (strcmp(password, PASSWORD) == 0) {
        isLoggedIn = 1;
        printf("Login successful.\n");
    } else {
        printf("Incorrect password. Login failed.\n");
    }
}

void changeEmail() {
    if (!isLoggedIn) {
        printf("You must be logged in to change your email.\n");
        return;
    }

    char oldEmail[MAX_EMAIL_LENGTH];
    char password[MAX_EMAIL_LENGTH];
    char newEmail[MAX_EMAIL_LENGTH];

    printf("Enter your current email: ");
    scanf("%s", oldEmail);
    if (strcmp(oldEmail, OLD_EMAIL) != 0) {
        printf("Incorrect old email.\n");
        return;
    }

    printf("Confirm your password: ");
    scanf("%s", password);
    if (strcmp(password, PASSWORD) != 0) {
        printf("Incorrect password.\n");
        return;
    }

    printf("Enter your new email: ");
    scanf("%s", newEmail);

    strcpy(OLD_EMAIL, newEmail); // Note: This is a simplification. In practice, you would update the actual storage.
    printf("Your email has been changed to %s.\n", OLD_EMAIL);
}

int main() {
    int choice;
    while (1) {
        printf("1. Login\n");
        printf("2. Change Email\n");
        printf("3. Exit\n");
        printf("Choose an option: ");
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
}