#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX_EMAIL_LENGTH 50
#define MAX_PASSWORD_LENGTH 20

typedef struct {
    char oldEmail[MAX_EMAIL_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
} UserCredentials;

bool verifyUser(UserCredentials user, const char* correctPassword) {
    return strcmp(user.password, correctPassword) == 0;
}

bool validateEmailChange(const char* oldEmail, const char* newEmail) {
    return strcmp(oldEmail, newEmail) != 0;
}

int main() {
    UserCredentials user;
    char newEmail[MAX_EMAIL_LENGTH];
    char confirmPassword[MAX_PASSWORD_LENGTH];
    const char* correctPassword = "correct_password"; // This should be securely stored and retrieved

    printf("Enter your old email: ");
    fgets(user.oldEmail, MAX_EMAIL_LENGTH, stdin);
    user.oldEmail[strcspn(user.oldEmail, "\n")] = 0; // Remove newline character

    printf("Enter your password: ");
    fgets(user.password, MAX_PASSWORD_LENGTH, stdin);
    user.password[strcspn(user.password, "\n")] = 0;

    if (!verifyUser(user, correctPassword)) {
        printf("Incorrect password. Please try again.\n");
        return 1;
    }

    printf("Enter your new email: ");
    fgets(newEmail, MAX_EMAIL_LENGTH, stdin);
    newEmail[strcspn(newEmail, "\n")] = 0;

    if (!validateEmailChange(user.oldEmail, newEmail)) {
        printf("New email must be different from the old email.\n");
        return 1;
    }

    printf("Confirm your password: ");
    fgets(confirmPassword, MAX_PASSWORD_LENGTH, stdin);
    confirmPassword[strcspn(confirmPassword, "\n")] = 0;

    if (strcmp(user.password, confirmPassword) != 0) {
        printf("Passwords do not match. Please try again.\n");
        return 1;
    }

    printf("Email changed successfully to %s\n", newEmail);
    return 0;
}