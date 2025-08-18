#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX_USERNAME 50
#define MAX_PASSWORD 50
#define MAX_EMAIL 100

typedef struct {
    char username[MAX_USERNAME];
    char password[MAX_PASSWORD];
    char email[MAX_EMAIL];
} User;

bool isLoggedIn = false;
User currentUser;

void login() {
    char username[MAX_USERNAME], password[MAX_PASSWORD];

    printf("Enter your username: ");
    scanf("%s", username);
    printf("Enter your password: ");
    scanf("%s", password);

    if (strcmp(username, "testuser") == 0 && strcmp(password, "testpass") == 0) {
        isLoggedIn = true;
        strncpy(currentUser.username, username, MAX_USERNAME);
        strncpy(currentUser.password, password, MAX_PASSWORD);
        strncpy(currentUser.email, "oldemail@example.com", MAX_EMAIL);
        printf("Login successful.\n");
    } else {
        printf("Invalid credentials.\n");
    }
}

void changeEmail() {
    if (!isLoggedIn) {
        printf("You must be logged in to change your email.\n");
        return;
    }

    char newEmail[MAX_EMAIL], confirmPassword[MAX_PASSWORD];

    printf("Enter your current password: ");
    scanf("%s", confirmPassword);

    if (strcmp(confirmPassword, currentUser.password) != 0) {
        printf("Incorrect password.\n");
        return;
    }

    printf("Enter your new email: ");
    scanf("%s", newEmail);

    if (strcmp(newEmail, currentUser.email) == 0) {
        printf("New email must be different from the old one.\n");
        return;
    }

    strncpy(currentUser.email, newEmail, MAX_EMAIL);
    printf("Email changed successfully.\n");
}

int main() {
    int choice;

    while (1) {
        printf("\nMenu:\n");
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

    return 0;
}