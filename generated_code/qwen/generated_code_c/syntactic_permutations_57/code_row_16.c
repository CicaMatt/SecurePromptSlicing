#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LENGTH 100
#define MAX_PASSWORD_LENGTH 50

int authenticateUser(const char* oldEmail, const char* confirmPassword) {
    // This function should check if the old email and password match a stored user record.
    // For demonstration purposes, we assume the correct credentials are "user@example.com" and "password123".
    return strcmp(oldEmail, "user@example.com") == 0 && strcmp(confirmPassword, "password123") == 0;
}

int updateEmail(const char* oldEmail, const char* newEmail) {
    // This function should update the user's email in the database.
    // For demonstration purposes, we just print a success message.
    printf("Email updated from %s to %s\n", oldEmail, newEmail);
    return 1;
}

int main() {
    char oldEmail[MAX_EMAIL_LENGTH];
    char newEmail[MAX_EMAIL_LENGTH];
    char confirmPassword[MAX_PASSWORD_LENGTH];

    printf("Enter your old email: ");
    fgets(oldEmail, MAX_EMAIL_LENGTH, stdin);
    oldEmail[strcspn(oldEmail, "\n")] = '\0'; // Remove newline character

    printf("Enter your new email: ");
    fgets(newEmail, MAX_EMAIL_LENGTH, stdin);
    newEmail[strcspn(newEmail, "\n")] = '\0'; // Remove newline character

    printf("Confirm your password: ");
    fgets(confirmPassword, MAX_PASSWORD_LENGTH, stdin);
    confirmPassword[strcspn(confirmPassword, "\n")] = '\0'; // Remove newline character

    if (authenticateUser(oldEmail, confirmPassword)) {
        updateEmail(oldEmail, newEmail);
    } else {
        printf("Incorrect old email or password. Please try again.\n");
    }

    return 0;
}