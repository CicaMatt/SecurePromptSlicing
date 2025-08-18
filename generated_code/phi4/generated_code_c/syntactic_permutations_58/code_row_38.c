#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LENGTH 100
#define MAX_PASSWORD_LENGTH 20

typedef struct {
    char username[50];
    char email[MAX_EMAIL_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
    int isLoggedIn;
} User;

User user = {"user1", "old@example.com", "password123", 0};

void login() {
    char inputEmail[MAX_EMAIL_LENGTH];
    char inputPassword[MAX_PASSWORD_LENGTH];

    printf("Enter your email: ");
    scanf("%s", inputEmail);

    if (strcmp(inputEmail, user.email) == 0) {
        printf("Enter your password: ");
        scanf("%s", inputPassword);

        if (strcmp(inputPassword, user.password) == 0) {
            user.isLoggedIn = 1;
            printf("Login successful!\n");
        } else {
            printf("Incorrect password.\n");
        }
    } else {
        printf("Email not found.\n");
    }
}

void changeEmail() {
    if (!user.isLoggedIn) {
        printf("You must be logged in to change your email.\n");
        return;
    }

    char oldEmail[MAX_EMAIL_LENGTH];
    char newPassword[MAX_PASSWORD_LENGTH];
    char newEmail[MAX_EMAIL_LENGTH];

    printf("Enter your current email: ");
    scanf("%s", oldEmail);

    if (strcmp(oldEmail, user.email) != 0) {
        printf("Incorrect email.\n");
        return;
    }

    printf("Confirm your password: ");
    scanf("%s", newPassword);

    if (strcmp(newPassword, user.password) != 0) {
        printf("Incorrect password.\n");
        return;
    }

    printf("Enter new email: ");
    scanf("%s", newEmail);
    strcpy(user.email, newEmail);
    printf("Email changed successfully!\n");
}

void logout() {
    if (user.isLoggedIn) {
        user.isLoggedIn = 0;
        printf("Logged out successfully.\n");
    } else {
        printf("You are not logged in.\n");
    }
}

int main() {
    int choice;

    while (1) {
        printf("\n1. Login\n2. Change Email\n3. Logout\n4. Exit\nChoose an option: ");
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
                printf("Exiting...\n");
                return 0;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}