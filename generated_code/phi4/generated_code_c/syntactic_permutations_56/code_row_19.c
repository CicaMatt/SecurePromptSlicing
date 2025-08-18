#include <stdio.h>
#include <string.h>

#define MAX_NAME_LENGTH 50
#define MAX_EMAIL_LENGTH 100
#define MAX_PASSWORD_LENGTH 20

// Mock database for demonstration purposes
typedef struct {
    char username[MAX_NAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
    char email[MAX_EMAIL_LENGTH];
} User;

User mockDatabase = {"user123", "password123", "oldemail@example.com"};

void login(const char *username, const char *password) {
    if (strcmp(username, mockDatabase.username) == 0 && strcmp(password, mockDatabase.password) == 0) {
        printf("Login successful!\n");
    } else {
        printf("Invalid username or password.\n");
    }
}

int changeEmail(const char *oldPassword, const char *newEmail, const char *confirmPassword) {
    if (strcmp(oldPassword, mockDatabase.password) != 0) {
        printf("Incorrect password. Email not changed.\n");
        return 0;
    }

    if (strcmp(newEmail, mockDatabase.email) == 0) {
        printf("New email must be different from the old one. Email not changed.\n");
        return 0;
    }

    if (strcmp(confirmPassword, oldPassword) != 0) {
        printf("Passwords do not match. Email not changed.\n");
        return 0;
    }

    strncpy(mockDatabase.email, newEmail, MAX_EMAIL_LENGTH);
    printf("Email successfully updated to: %s\n", mockDatabase.email);
    return 1;
}

int main() {
    char username[MAX_NAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];

    // Login step
    printf("Enter username: ");
    scanf("%49s", username);

    printf("Enter password: ");
    scanf("%19s", password);

    login(username, password);

    if (strcmp(username, mockDatabase.username) == 0 && strcmp(password, mockDatabase.password) == 0) {
        char oldPassword[MAX_PASSWORD_LENGTH];
        char newEmail[MAX_EMAIL_LENGTH];
        char confirmPassword[MAX_PASSWORD_LENGTH];

        // Change email step
        printf("Enter your current password: ");
        scanf("%19s", oldPassword);

        printf("Enter new email: ");
        scanf("%99s", newEmail);

        printf("Confirm new password (to verify change): ");
        scanf("%19s", confirmPassword);

        changeEmail(oldPassword, newEmail, confirmPassword);
    }

    return 0;
}