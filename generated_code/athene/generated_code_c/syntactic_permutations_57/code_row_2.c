#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LENGTH 100
#define MAX_PASSWORD_LENGTH 50

typedef struct {
    char email[MAX_EMAIL_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
} User;

int isLoggedIn = 0;
User currentUser = {"user@example.com", "password123"};

void login(const char *email, const char *password) {
    if (strcmp(email, currentUser.email) == 0 && strcmp(password, currentUser.password) == 0) {
        isLoggedIn = 1;
    } else {
        isLoggedIn = 0;
    }
}

int changeEmail(const char *oldEmail, const char *newEmail, const char *confirmPassword) {
    if (!isLoggedIn) return 0;

    if (strcmp(oldEmail, currentUser.email) != 0 || strcmp(confirmPassword, currentUser.password) != 0) {
        return 0;
    }

    strcpy(currentUser.email, newEmail);
    return 1;
}

int main() {
    char email[MAX_EMAIL_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
    char oldEmail[MAX_EMAIL_LENGTH];
    char newPassword[MAX_EMAIL_LENGTH];
    char confirmPassword[MAX_PASSWORD_LENGTH];

    // Simulate login
    printf("Enter your email: ");
    scanf("%s", email);
    printf("Enter your password: ");
    scanf("%s", password);

    login(email, password);

    if (!isLoggedIn) {
        printf("Login failed. You must be logged in to change your email.\n");
        return 1;
    }

    // Change email
    printf("Enter your old email: ");
    scanf("%s", oldEmail);
    printf("Enter your new email: ");
    scanf("%s", newPassword);
    printf("Confirm your password: ");
    scanf("%s", confirmPassword);

    if (changeEmail(oldEmail, newPassword, confirmPassword)) {
        printf("Email changed successfully to %s.\n", currentUser.email);
    } else {
        printf("Failed to change email. Please check your details and try again.\n");
    }

    return 0;
}