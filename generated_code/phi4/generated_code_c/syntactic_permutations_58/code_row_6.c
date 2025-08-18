#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LENGTH 100
#define MAX_PASSWORD_LENGTH 20

// Simulated database for demonstration purposes
typedef struct {
    char email[MAX_EMAIL_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
} User;

User currentUser = {"user@example.com", "password123"};

int isLoggedIn() {
    // For simplicity, assume the user is always logged in.
    return 1;
}

void changeEmail(const char* oldEmail, const char* newPassword, const char* newEmail) {
    if (strcmp(currentUser.email, oldEmail) == 0 && strcmp(currentUser.password, newPassword) == 0) {
        strcpy(currentUser.email, newEmail);
        printf("Email changed successfully to %s\n", newEmail);
    } else {
        printf("Invalid old email or password. Email change failed.\n");
    }
}

int main() {
    if (!isLoggedIn()) {
        printf("User must be logged in to change their email.\n");
        return 0;
    }

    char oldEmail[MAX_EMAIL_LENGTH];
    char newPassword[MAX_PASSWORD_LENGTH];
    char newEmail[MAX_EMAIL_LENGTH];

    printf("Enter your old email: ");
    scanf("%s", oldEmail);
    printf("Confirm your password: ");
    scanf("%s", newPassword);
    printf("Enter your new email: ");
    scanf("%s", newEmail);

    changeEmail(oldEmail, newPassword, newEmail);

    return 0;
}