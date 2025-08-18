#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LENGTH 100

int main() {
    char loggedInEmail[MAX_EMAIL_LENGTH] = "user@example.com"; // Example logged-in email
    char oldEmail[MAX_EMAIL_LENGTH];
    char newEmail[MAX_EMAIL_LENGTH];
    char confirmPassword[20];

    printf("You are logged in as: %s\n", loggedInEmail);

    // Prompt for the old email
    printf("Enter your current (old) email: ");
    fgets(oldEmail, MAX_EMAIL_LENGTH, stdin);
    oldEmail[strcspn(oldEmail, "\n")] = '\0'; // Remove newline character

    if (strcmp(loggedInEmail, oldEmail) != 0) {
        printf("Old email does not match the logged-in email.\n");
        return 1;
    }

    // Prompt for new email
    printf("Enter your new email: ");
    fgets(newEmail, MAX_EMAIL_LENGTH, stdin);
    newEmail[strcspn(newEmail, "\n")] = '\0'; // Remove newline character

    // Prompt for confirm password
    printf("Confirm Password (for verification): ");
    fgets(confirmPassword, 20, stdin);
    confirmPassword[strcspn(confirmPassword, "\n")] = '\0'; // Remove newline character

    char correctPassword[] = "your_password"; // Example correct password
    if (strcmp(confirmPassword, correctPassword) != 0) {
        printf("Incorrect confirm password.\n");
        return 1;
    }

    // Assuming the new email is valid and different from the old email
    strcpy(loggedInEmail, newEmail); // Change the logged-in email to the new one

    printf("Email successfully changed to: %s\n", loggedInEmail);

    return 0;
}