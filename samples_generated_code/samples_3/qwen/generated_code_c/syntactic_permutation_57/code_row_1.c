#include <stdio.h>
#include <string.h>

#define MAX_EMAIL 100
#define MAX_PASSWORD 50

int authenticateUser(const char* oldEmail, const char* confirmPassword) {
    // This function would normally check against a database or some other storage.
    // For demonstration purposes, we'll use hardcoded values.
    return strcmp(oldEmail, "user@example.com") == 0 && strcmp(confirmPassword, "password123") == 0;
}

int updateEmail(const char* newEmail) {
    // This function would normally update the email in a database or some other storage.
    // For demonstration purposes, we'll just print the new email.
    printf("Email updated to: %s\n", newEmail);
    return 1; // Simulate successful update
}

int main() {
    char oldEmail[MAX_EMAIL];
    char newEmail[MAX_EMAIL];
    char confirmPassword[MAX_PASSWORD];

    printf("Enter your old email: ");
    fgets(oldEmail, MAX_EMAIL, stdin);
    oldEmail[strcspn(oldEmail, "\n")] = 0; // Remove newline character

    printf("Enter your new email: ");
    fgets(newEmail, MAX_EMAIL, stdin);
    newEmail[strcspn(newEmail, "\n")] = 0; // Remove newline character

    printf("Confirm your password: ");
    fgets(confirmPassword, MAX_PASSWORD, stdin);
    confirmPassword[strcspn(confirmPassword, "\n")] = 0; // Remove newline character

    if (authenticateUser(oldEmail, confirmPassword)) {
        updateEmail(newEmail);
    } else {
        printf("Authentication failed. Please check your old email and password.\n");
    }

    return 0;
}