#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LENGTH 100
#define MAX_PASSWORD_LENGTH 50

typedef struct {
    char email[MAX_EMAIL_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
} User;

int isLoggedIn = 0;
User currentUser = {"example@example.com", "password123"};

void login(const char *email, const char *password) {
    if (strcmp(email, currentUser.email) == 0 && strcmp(password, currentUser.password) == 0) {
        isLoggedIn = 1;
        printf("Login successful.\n");
    } else {
        printf("Login failed. Incorrect email or password.\n");
    }
}

int changeEmail(const char *oldEmail, const char *newEmail, const char *confirmPassword) {
    if (!isLoggedIn) {
        printf("You must be logged in to change your email.\n");
        return 0;
    }

    if (strcmp(oldEmail, currentUser.email) != 0) {
        printf("The provided old email does not match the current user's email.\n");
        return 0;
    }

    if (strcmp(confirmPassword, currentUser.password) != 0) {
        printf("Incorrect confirm password.\n");
        return 0;
    }

    strcpy(currentUser.email, newEmail);
    printf("Email changed successfully to: %s\n", currentUser.email);
    return 1;
}

int main() {
    char email[MAX_EMAIL_LENGTH], password[MAX_PASSWORD_LENGTH];
    char oldEmail[MAX_EMAIL_LENGTH], newEmail[MAX_EMAIL_LENGTH], confirmPassword[MAX_PASSWORD_LENGTH];

    // Simulate login
    printf("Enter your email: ");
    scanf("%99s", email);
    printf("Enter your password: ");
    scanf("%49s", password);

    login(email, password);

    if (isLoggedIn) {
        // Change email process
        printf("Enter your old email: ");
        scanf("%99s", oldEmail);
        printf("Enter your new email: ");
        scanf("%99s", newEmail);
        printf("Confirm your password: ");
        scanf("%49s", confirmPassword);

        changeEmail(oldEmail, newEmail, confirmPassword);
    }

    return 0;
}