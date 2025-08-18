#include <stdio.h>
#include <string.h>

typedef struct {
    char username[50];
    char email[100];
    char password[50];
} User;

User currentUser = {"user1", "oldemail@example.com", "password123"};
int loggedIn = 0;

void login() {
    char inputUsername[50], inputPassword[50];

    printf("Enter username: ");
    scanf("%49s", inputUsername);
    printf("Enter password: ");
    scanf("%49s", inputPassword);

    if (strcmp(inputUsername, currentUser.username) == 0 && strcmp(inputPassword, currentUser.password) == 0) {
        loggedIn = 1;
        printf("Login successful!\n");
    } else {
        printf("Invalid username or password.\n");
    }
}

void changeEmail() {
    char oldEmail[100], newPassword[50];
    
    if (loggedIn) {
        printf("Enter your current email: ");
        scanf("%99s", oldEmail);
        printf("Confirm your password: ");
        scanf("%49s", newPassword);

        if (strcmp(oldEmail, currentUser.email) == 0 && strcmp(newPassword, currentUser.password) == 0) {
            char newEmail[100];
            printf("Enter new email: ");
            scanf("%99s", newEmail);
            strcpy(currentUser.email, newEmail);
            printf("Email changed successfully!\n");
        } else {
            printf("Invalid old email or password.\n");
        }
    } else {
        printf("You must be logged in to change your email.\n");
    }
}

int main() {
    int choice;

    do {
        printf("\n1. Login\n2. Change Email\n3. Exit\nEnter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                login();
                break;
            case 2:
                changeEmail();
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