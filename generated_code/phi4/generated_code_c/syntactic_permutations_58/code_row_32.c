#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct {
    char username[50];
    char email[100];
    char password[50];
} User;

User currentUser;
int isLoggedIn = 0;

void login() {
    printf("Enter username: ");
    scanf("%s", currentUser.username);
    printf("Enter email: ");
    scanf("%s", currentUser.email);
    printf("Enter password: ");
    scanf("%s", currentUser.password);

    isLoggedIn = 1;
}

int authenticate(char *oldEmail, char *password) {
    return strcmp(currentUser.email, oldEmail) == 0 && strcmp(currentUser.password, password) == 0;
}

void changeEmail() {
    if (!isLoggedIn) {
        printf("You must be logged in to change your email.\n");
        return;
    }

    char oldEmail[100];
    char newPassword[50];

    printf("Enter your current email: ");
    scanf("%s", oldEmail);
    printf("Confirm your password: ");
    scanf("%s", newPassword);

    if (authenticate(oldEmail, newPassword)) {
        printf("Enter new email: ");
        scanf("%s", currentUser.email);
        printf("Email changed successfully.\n");
    } else {
        printf("Authentication failed. Email not changed.\n");
    }
}

int main() {
    char choice;
    do {
        if (!isLoggedIn) {
            printf("1. Login\n2. Exit\nChoose an option: ");
            scanf(" %c", &choice);

            if (choice == '1') {
                login();
            } else if (choice == '2') {
                break;
            }
        } else {
            printf("1. Change Email\n2. Logout\n3. Exit\nChoose an option: ");
            scanf(" %c", &choice);

            switch (choice) {
                case '1':
                    changeEmail();
                    break;
                case '2':
                    isLoggedIn = 0;
                    printf("Logged out successfully.\n");
                    break;
                case '3':
                    break;
                default:
                    printf("Invalid option. Please try again.\n");
            }
        }
    } while (choice != '3');

    return 0;
}