#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LENGTH 100
#define MAX_PASSWORD_LENGTH 50

typedef struct {
    char oldEmail[MAX_EMAIL_LENGTH];
    char newEmail[MAX_EMAIL_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
} User;

int verifyPassword(const char* enteredPassword, const char* storedPassword) {
    return strcmp(enteredPassword, storedPassword) == 0;
}

void changeEmail(User* user) {
    char oldEmailInput[MAX_EMAIL_LENGTH];
    char newEmailInput[MAX_EMAIL_LENGTH];
    char passwordInput[MAX_PASSWORD_LENGTH];
    const char* storedOldEmail = "user@example.com"; // This should be fetched from a database
    const char* storedPassword = "password123";      // This should be fetched from a database

    printf("Enter your old email: ");
    fgets(oldEmailInput, sizeof(oldEmailInput), stdin);
    oldEmailInput[strcspn(oldEmailInput, "\n")] = 0;

    if (strcmp(oldEmailInput, storedOldEmail) != 0) {
        printf("Incorrect old email.\n");
        return;
    }

    printf("Enter your password: ");
    fgets(passwordInput, sizeof(passwordInput), stdin);
    passwordInput[strcspn(passwordInput, "\n")] = 0;

    if (!verifyPassword(passwordInput, storedPassword)) {
        printf("Incorrect password.\n");
        return;
    }

    printf("Enter your new email: ");
    fgets(newEmailInput, sizeof(newEmailInput), stdin);
    newEmailInput[strcspn(newEmailInput, "\n")] = 0;

    printf("Confirm your new email: ");
    char confirmNewEmail[MAX_EMAIL_LENGTH];
    fgets(confirmNewEmail, sizeof(confirmNewEmail), stdin);
    confirmNewEmail[strcspn(confirmNewEmail, "\n")] = 0;

    if (strcmp(newEmailInput, confirmNewEmail) != 0) {
        printf("New email and confirmation do not match.\n");
        return;
    }

    strcpy(user->oldEmail, oldEmailInput);
    strcpy(user->newEmail, newEmailInput);

    printf("Email changed successfully.\n");
}

int main() {
    User user;

    printf("Login to change your email:\n");

    changeEmail(&user);

    return 0;
}