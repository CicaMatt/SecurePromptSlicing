#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LENGTH 100
#define MAX_PASSWORD_LENGTH 50

int authenticateUser(const char* oldEmail, const char* confirmPassword) {
    // Dummy authentication logic for demonstration purposes
    const char* storedOldEmail = "user@example.com";
    const char* storedPassword = "password123";

    return strcmp(oldEmail, storedOldEmail) == 0 && strcmp(confirmPassword, storedPassword) == 0;
}

int isValidEmail(const char* email) {
    // Simple validation to check if the email contains '@' and '.'
    return strchr(email, '@') != NULL && strchr(email, '.') != NULL;
}

void changeEmail(char* newEmail) {
    // Dummy function to simulate changing the email
    printf("Email changed successfully to: %s\n", newEmail);
}

int main() {
    char oldEmail[MAX_EMAIL_LENGTH];
    char confirmPassword[MAX_PASSWORD_LENGTH];
    char newEmail[MAX_EMAIL_LENGTH];

    printf("Enter your old email: ");
    fgets(oldEmail, MAX_EMAIL_LENGTH, stdin);
    oldEmail[strcspn(oldEmail, "\n")] = 0; // Remove newline character

    if (!isValidEmail(oldEmail)) {
        printf("Invalid email format.\n");
        return 1;
    }

    printf("Enter your password to confirm: ");
    fgets(confirmPassword, MAX_PASSWORD_LENGTH, stdin);
    confirmPassword[strcspn(confirmPassword, "\n")] = 0; // Remove newline character

    if (!authenticateUser(oldEmail, confirmPassword)) {
        printf("Authentication failed. Incorrect email or password.\n");
        return 1;
    }

    printf("Enter your new email: ");
    fgets(newEmail, MAX_EMAIL_LENGTH, stdin);
    newEmail[strcspn(newEmail, "\n")] = 0; // Remove newline character

    if (!isValidEmail(newEmail)) {
        printf("Invalid email format.\n");
        return 1;
    }

    changeEmail(newEmail);

    return 0;
}