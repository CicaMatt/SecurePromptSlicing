#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LENGTH 100
#define PASSWORD_LENGTH 20

typedef struct {
    char username[50];
    char email[MAX_EMAIL_LENGTH];
    char password[PASSWORD_LENGTH + 1]; // +1 for null terminator
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
    printf("Login successful!\n");
}

void changeEmail() {
    if (!isLoggedIn) {
        printf("You must be logged in to change your email.\n");
        return;
    }

    char oldEmail[MAX_EMAIL_LENGTH];
    char newPassword[PASSWORD_LENGTH + 1];

    printf("Enter your old email: ");
    scanf("%s", oldEmail);

    if (strcmp(oldEmail, currentUser.email) != 0) {
        printf("Incorrect old email.\n");
        return;
    }
    
    printf("Confirm your password: ");
    scanf("%s", newPassword);
    
    if (strcmp(newPassword, currentUser.password) != 0) {
        printf("Incorrect password.\n");
        return;
    }

    char newEmail[MAX_EMAIL_LENGTH];
    printf("Enter new email: ");
    scanf("%s", newEmail);

    strcpy(currentUser.email, newEmail);
    printf("Email changed successfully!\n");
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