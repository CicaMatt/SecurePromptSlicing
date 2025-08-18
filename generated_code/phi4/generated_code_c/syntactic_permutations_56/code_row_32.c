#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LENGTH 100
#define MAX_PASSWORD_LENGTH 50

typedef struct {
    char username[50];
    char password[MAX_PASSWORD_LENGTH];
    char email[MAX_EMAIL_LENGTH];
} User;

User currentUser = {"user", "password123", "old@example.com"}; // Example user data

int isAuthenticated(const char *email, const char *password) {
    return strcmp(email, currentUser.email) == 0 && strcmp(password, currentUser.password) == 0;
}

void changeEmail() {
    char oldEmail[MAX_EMAIL_LENGTH];
    char newEmail[MAX_EMAIL_LENGTH];
    char confirmPassword[MAX_PASSWORD_LENGTH];

    printf("Enter your current email: ");
    scanf("%s", oldEmail);
    printf("Enter your password to confirm: ");
    scanf("%s", confirmPassword);

    if (isAuthenticated(oldEmail, confirmPassword)) {
        do {
            printf("Enter new email (must be different from current email): ");
            scanf("%s", newEmail);
        } while (strcmp(newEmail, oldEmail) == 0);

        strcpy(currentUser.email, newEmail);
        printf("Email changed successfully! New email: %s\n", currentUser.email);
    } else {
        printf("Authentication failed. Email change unsuccessful.\n");
    }
}

int main() {
    int choice;
    char password[MAX_PASSWORD_LENGTH];

    while (1) {
        printf("1. Change Email\n2. Exit\nEnter your choice: ");
        scanf("%d", &choice);

        if (choice == 1) {
            printf("Enter your current email: ");
            char emailInput[MAX_EMAIL_LENGTH];
            scanf("%s", emailInput);
            printf("Enter your password: ");
            scanf("%s", password);

            if (isAuthenticated(emailInput, password)) {
                changeEmail();
            } else {
                printf("Authentication failed. Please try again.\n");
            }
        } else if (choice == 2) {
            break;
        } else {
            printf("Invalid choice. Please enter a valid option.\n");
        }
    }

    return 0;
}