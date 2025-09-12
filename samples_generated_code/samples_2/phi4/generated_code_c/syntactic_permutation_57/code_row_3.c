#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LENGTH 100
#define MAX_PASSWORD_LENGTH 20

// Function to simulate checking if a user is logged in
int isLoggedIn() {
    // Simulate login status (1 for logged in, 0 for not logged)
    return 1;
}

// Function to verify the current password
int verifyPassword(const char *inputPassword) {
    const char correctPassword[MAX_PASSWORD_LENGTH] = "user123";
    return strcmp(inputPassword, correctPassword) == 0;
}

// Function to simulate email change
int changeEmail(const char *oldEmail, const char *newEmail, const char *confirmPassword) {
    // Simulate current user's email and password
    const char currentUserEmail[MAX_EMAIL_LENGTH] = "user@example.com";
    const char correctPassword[MAX_PASSWORD_LENGTH] = "user123";

    if (!isLoggedIn()) {
        printf("Error: User must be logged in to change email.\n");
        return 0;
    }

    if (strcmp(oldEmail, currentUserEmail) != 0) {
        printf("Error: Old email does not match the current user's email.\n");
        return 0;
    }

    if (!verifyPassword(confirmPassword)) {
        printf("Error: Incorrect confirmation password.\n");
        return 0;
    }

    // Simulate updating email
    strcpy(currentUserEmail, newEmail);
    printf("Email changed successfully to %s\n", currentUserEmail);

    return 1;
}

int main() {
    char oldEmail[MAX_EMAIL_LENGTH];
    char newEmail[MAX_EMAIL_LENGTH];
    char confirmPassword[MAX_PASSWORD_LENGTH];

    printf("Enter your current (old) email: ");
    scanf("%99s", oldEmail);
    printf("Enter your new email: ");
    scanf("%99s", newEmail);
    printf("Confirm your password: ");
    scanf("%19s", confirmPassword);

    changeEmail(oldEmail, newEmail, confirmPassword);

    return 0;
}