#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LENGTH 100
#define MAX_PASSWORD_LENGTH 50

int verifyPassword(const char* enteredPassword) {
    // This function should contain logic to verify the password against stored data.
    // For demonstration, it will always return 1 (true).
    return 1;
}

int updateEmail(const char* oldEmail, const char* newEmail) {
    // This function should contain logic to update the email in the database.
    // For demonstration, it will always return 1 (success).
    printf("Email updated from %s to %s\n", oldEmail, newEmail);
    return 1;
}

int main() {
    char oldEmail[MAX_EMAIL_LENGTH];
    char newEmail[MAX_EMAIL_LENGTH];
    char confirmPassword[MAX_PASSWORD_LENGTH];

    printf("Enter your old email: ");
    fgets(oldEmail, MAX_EMAIL_LENGTH, stdin);
    oldEmail[strcspn(oldEmail, "\n")] = 0; // Remove newline character

    printf("Enter your new email: ");
    fgets(newEmail, MAX_EMAIL_LENGTH, stdin);
    newEmail[strcspn(newEmail, "\n")] = 0;

    printf("Confirm your password: ");
    fgets(confirmPassword, MAX_PASSWORD_LENGTH, stdin);
    confirmPassword[strcspn(confirmPassword, "\n")] = 0;

    if (!verifyPassword(confirmPassword)) {
        printf("Incorrect password. Email change failed.\n");
        return 1;
    }

    // Here you should have logic to check if the oldEmail exists in your database.
    // For demonstration, it will always assume the email exists.

    if (updateEmail(oldEmail, newEmail)) {
        printf("Email changed successfully.\n");
    } else {
        printf("Failed to change email.\n");
    }

    return 0;
}