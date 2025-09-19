#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LENGTH 100
#define MAX_PASSWORD_LENGTH 50

typedef struct {
    char email[MAX_EMAIL_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
} User;

User currentUser;
int loggedIn = 0;

void login() {
    printf("Enter your email: ");
    scanf("%s", currentUser.email);
    printf("Enter your password: ");
    scanf("%s", currentUser.password);
    
    // Simulate checking credentials
    if (strcmp(currentUser.email, "user@example.com") == 0 && strcmp(currentUser.password, "password123") == 0) {
        loggedIn = 1;
        printf("Login successful!\n");
    } else {
        printf("Invalid email or password.\n");
    }
}

void changeEmail() {
    if (!loggedIn) {
        printf("You must be logged in to change your email.\n");
        return;
    }

    char oldEmail[MAX_EMAIL_LENGTH];
    char newPassword[MAX_PASSWORD_LENGTH];

    printf("Enter your current (old) email: ");
    scanf("%s", oldEmail);
    printf("Re-enter your password for confirmation: ");
    scanf("%s", newPassword);

    if (strcmp(oldEmail, currentUser.email) == 0 && strcmp(newPassword, currentUser.password) == 0) {
        char newEmail[MAX_EMAIL_LENGTH];
        printf("Enter your new email: ");
        scanf("%s", newEmail);
        strcpy(currentUser.email, newEmail);
        printf("Email changed successfully to %s.\n", currentUser.email);
    } else {
        printf("Old email or password did not match. Email change failed.\n");
    }
}

int main() {
    login();
    
    if (loggedIn) {
        char option;
        do {
            printf("\nDo you want to change your email? (y/n): ");
            scanf(" %c", &option);
            
            if (option == 'y' || option == 'Y') {
                changeEmail();
            } else if (option != 'n' && option != 'N') {
                printf("Invalid input. Please enter 'y' or 'n'.\n");
            }
        } while(option != 'n' && option != 'N');
    }

    return 0;
}