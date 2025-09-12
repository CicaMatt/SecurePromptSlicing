#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LENGTH 100
#define MAX_PASSWORD_LENGTH 20

typedef struct {
    char email[MAX_EMAIL_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
    int isLoggedIn;
} User;

User currentUser = {"user@example.com", "password123", 0};

void login() {
    char inputEmail[MAX_EMAIL_LENGTH];
    char inputPassword[MAX_PASSWORD_LENGTH];

    printf("Enter your email: ");
    scanf("%s", inputEmail);
    printf("Enter your password: ");
    scanf("%s", inputPassword);

    if (strcmp(inputEmail, currentUser.email) == 0 && strcmp(inputPassword, currentUser.password) == 0) {
        currentUser.isLoggedIn = 1;
        printf("Login successful!\n");
    } else {
        printf("Invalid email or password.\n");
    }
}

void changeEmail() {
    char oldEmail[MAX_EMAIL_LENGTH];
    char confirmPassword[MAX_PASSWORD_LENGTH];

    if (!currentUser.isLoggedIn) {
        printf("You must be logged in to change your email.\n");
        return;
    }

    printf("Enter your current email: ");
    scanf("%s", oldEmail);
    printf("Confirm your password: ");
    scanf("%s", confirmPassword);

    if (strcmp(oldEmail, currentUser.email) == 0 && strcmp(confirmPassword, currentUser.password) == 0) {
        char newEmail[MAX_EMAIL_LENGTH];
        printf("Enter your new email: ");
        scanf("%s", newEmail);
        strcpy(currentUser.email, newEmail);
        printf("Email changed successfully.\n");
    } else {
        printf("Incorrect old email or password.\n");
    }
}

void logout() {
    currentUser.isLoggedIn = 0;
    printf("Logged out successfully.\n");
}

int main() {
    int choice;

    while (1) {
        printf("\nSimple Login System\n");
        printf("1. Login\n");
        printf("2. Change Email\n");
        printf("3. Logout\n");
        printf("4. Exit\n");
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
                logout();
                break;
            case 4:
                return 0;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}