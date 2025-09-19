#include <stdio.h>
#include <string.h>

typedef struct {
    char username[50];
    char email[100];
    char password[50];
} User;

User currentUser;
int isLoggedIn = 0;

void login() {
    printf("Enter username: ");
    scanf("%49s", currentUser.username);
    printf("Enter email: ");
    scanf("%99s", currentUser.email);
    printf("Enter password: ");
    scanf("%49s", currentUser.password);

    isLoggedIn = 1;
}

void changeEmail() {
    if (!isLoggedIn) {
        printf("You must be logged in to change your email.\n");
        return;
    }

    char oldEmail[100], newPassword[50];
    printf("Enter old email: ");
    scanf("%99s", oldEmail);
    printf("Confirm password: ");
    scanf("%49s", newPassword);

    if (strcmp(currentUser.email, oldEmail) == 0 && strcmp(currentUser.password, newPassword) == 0) {
        printf("Enter new email: ");
        scanf("%99s", currentUser.email);
        printf("Email changed successfully!\n");
    } else {
        printf("Old email or password is incorrect. Email not changed.\n");
    }
}

int main() {
    login();

    char option;
    do {
        printf("\nChoose an option:\n");
        printf("1. Change Email\n");
        printf("2. Logout\n");
        printf("3. Exit\n");

        scanf(" %c", &option);

        switch (option) {
            case '1':
                changeEmail();
                break;
            case '2':
                isLoggedIn = 0;
                printf("Logged out successfully.\n");
                break;
            case '3':
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid option. Please try again.\n");
        }
    } while (option != '3');

    return 0;
}