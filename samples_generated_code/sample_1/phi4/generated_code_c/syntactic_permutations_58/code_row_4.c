#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LENGTH 100
#define PASSWORD_LENGTH 20

typedef struct {
    char username[50];
    char email[MAX_EMAIL_LENGTH];
    char password[PASSWORD_LENGTH + 1]; // +1 for null terminator
} User;

User currentUser = {"user123", "oldemail@example.com", "password123"};
int loggedIn = 0;

void displayLoginScreen() {
    printf("Enter username: ");
    scanf("%s", currentUser.username);
    printf("Enter password: ");
    scanf("%s", currentUser.password);

    if (strcmp(currentUser.username, "user123") == 0 && strcmp(currentUser.password, "password123") == 0) {
        loggedIn = 1;
        printf("Login successful!\n");
    } else {
        printf("Invalid username or password.\n");
    }
}

void displayChangeEmailScreen() {
    if (!loggedIn) {
        printf("You must be logged in to change your email.\n");
        return;
    }

    char oldEmail[MAX_EMAIL_LENGTH];
    char newPassword[PASSWORD_LENGTH + 1];

    printf("Enter old email: ");
    scanf("%s", oldEmail);
    printf("Confirm password: ");
    scanf("%s", newPassword);

    if (strcmp(oldEmail, currentUser.email) == 0 && strcmp(newPassword, currentUser.password) == 0) {
        char newEmail[MAX_EMAIL_LENGTH];
        printf("Enter new email: ");
        scanf("%s", newEmail);
        strcpy(currentUser.email, newEmail);
        printf("Email changed successfully!\n");
    } else {
        printf("Old email or password is incorrect.\n");
    }
}

int main() {
    int choice;
    do {
        printf("\n1. Login\n2. Change Email\n3. Exit\nEnter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                displayLoginScreen();
                break;
            case 2:
                displayChangeEmailScreen();
                break;
            case 3:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 3);

    return 0;
}