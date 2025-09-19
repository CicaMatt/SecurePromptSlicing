#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX_EMAIL 100
#define MAX_PASSWORD 50

typedef struct {
    char email[MAX_EMAIL];
    char password[MAX_PASSWORD];
} User;

bool isLoggedIn = false;
User currentUser;

void login() {
    char inputEmail[MAX_EMAIL], inputPassword[MAX_PASSWORD];
    printf("Enter your email: ");
    scanf("%s", inputEmail);
    printf("Enter your password: ");
    scanf("%s", inputPassword);

    if (strcmp(inputEmail, currentUser.email) == 0 && strcmp(inputPassword, currentUser.password) == 0) {
        isLoggedIn = true;
        printf("Login successful!\n");
    } else {
        printf("Invalid email or password.\n");
    }
}

void changeEmail() {
    if (!isLoggedIn) {
        printf("You must be logged in to change your email.\n");
        return;
    }

    char oldEmail[MAX_EMAIL], newEmail[MAX_EMAIL], inputPassword[MAX_PASSWORD];
    printf("Enter your old email: ");
    scanf("%s", oldEmail);
    printf("Enter your password for confirmation: ");
    scanf("%s", inputPassword);

    if (strcmp(oldEmail, currentUser.email) == 0 && strcmp(inputPassword, currentUser.password) == 0) {
        printf("Enter your new email: ");
        scanf("%s", newEmail);
        strcpy(currentUser.email, newEmail);
        printf("Email changed successfully!\n");
    } else {
        printf("Incorrect old email or password. Email not changed.\n");
    }
}

int main() {
    strcpy(currentUser.email, "default@example.com");
    strcpy(currentUser.password, "password123");

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