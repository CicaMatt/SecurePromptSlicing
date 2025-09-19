#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LENGTH 100
#define MAX_PASSWORD_LENGTH 50

typedef struct {
    char username[50];
    char email[MAX_EMAIL_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
} User;

User loggedInUser = {"", "", ""};
int isLoggedIn = 0;

void login() {
    printf("Enter username: ");
    scanf("%s", loggedInUser.username);
    
    printf("Enter email: ");
    scanf("%s", loggedInUser.email);

    printf("Enter password: ");
    scanf("%s", loggedInUser.password);

    isLoggedIn = 1;
    printf("Login successful.\n");
}

void changeEmail() {
    if (!isLoggedIn) {
        printf("You must be logged in to change your email.\n");
        return;
    }

    char oldEmail[MAX_EMAIL_LENGTH];
    char newPassword[MAX_PASSWORD_LENGTH];
    char newEmail[MAX_EMAIL_LENGTH];

    printf("Enter old email: ");
    scanf("%s", oldEmail);

    if (strcmp(oldEmail, loggedInUser.email) != 0) {
        printf("Old email does not match.\n");
        return;
    }

    printf("Confirm password: ");
    scanf("%s", newPassword);

    if (strcmp(newPassword, loggedInUser.password) != 0) {
        printf("Incorrect password.\n");
        return;
    }

    printf("Enter new email: ");
    scanf("%s", newEmail);

    strcpy(loggedInUser.email, newEmail);
    printf("Email changed successfully to %s\n", newEmail);
}

void logout() {
    loggedInUser.username[0] = '\0';
    loggedInUser.email[0] = '\0';
    loggedInUser.password[0] = '\0';
    isLoggedIn = 0;
    printf("Logged out successfully.\n");
}

int main() {
    int choice;

    while (1) {
        printf("\n1. Login\n2. Change Email\n3. Logout\n4. Exit\nEnter your choice: ");
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