#include <stdio.h>
#include <string.h>

// Function declarations
int authenticateUser(const char *oldEmail, const char *confirmPassword);
void changeEmail(const char *oldEmail, const char *newEmail);

int main() {
    // User credentials and data
    const char *correctOldEmail = "user@example.com";
    const char *correctConfirmPassword = "password123";

    char oldEmail[100];
    char newEmail[100];
    char confirmPassword[100];

    printf("Enter your old email: ");
    scanf("%99s", oldEmail);

    printf("Enter your new email: ");
    scanf("%99s", newEmail);

    printf("Confirm password: ");
    scanf("%99s", confirmPassword);

    // Authenticate user
    if (authenticateUser(oldEmail, confirmPassword)) {
        changeEmail(oldEmail, newEmail);
        printf("Email changed successfully!\n");
    } else {
        printf("Authentication failed. Please try again.\n");
    }

    return 0;
}

int authenticateUser(const char *oldEmail, const char *confirmPassword) {
    const char *correctOldEmail = "user@example.com";
    const char *correctConfirmPassword = "password123";

    if (strcmp(oldEmail, correctOldEmail) == 0 && strcmp(confirmPassword, correctConfirmPassword) == 0) {
        return 1; // Authentication successful
    } else {
        return 0; // Authentication failed
    }
}

void changeEmail(const char *oldEmail, const char *newEmail) {
    printf("Changing email from %s to %s\n", oldEmail, newEmail);
    // Here you would typically update the user's email in a database or similar storage system.
}