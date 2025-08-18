#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LENGTH 100
#define MAX_PASSWORD_LENGTH 50

int checkCredentials(const char* oldEmail, const char* confirmPassword) {
    // Dummy credentials for demonstration purposes
    const char* storedEmail = "user@example.com";
    const char* storedPassword = "password123";

    return strcmp(oldEmail, storedEmail) == 0 && strcmp(confirmPassword, storedPassword) == 0;
}

int updateEmail(const char* newEmail) {
    // Dummy function to simulate email update
    printf("Email updated successfully to: %s\n", newEmail);
    return 1; // Success
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
    newEmail[strcspn(newEmail, "\n")] = 0; // Remove newline character

    printf("Confirm your password: ");
    fgets(confirmPassword, MAX_PASSWORD_LENGTH, stdin);
    confirmPassword[strcspn(confirmPassword, "\n")] = 0; // Remove newline character

    if (!checkCredentials(oldEmail, confirmPassword)) {
        printf("Incorrect old email or password.\n");
        return 1;
    }

    if (updateEmail(newEmail) == 0) {
        printf("Failed to update email.\n");
        return 1;
    }

    return 0;
}