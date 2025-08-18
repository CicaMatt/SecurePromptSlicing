#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LENGTH 100
#define MAX_PASSWORD_LENGTH 50

// Function to simulate checking if the old email exists and the password is correct
int verifyUser(const char* oldEmail, const char* password) {
    // Dummy data for demonstration purposes
    const char* storedEmail = "user@example.com";
    const char* storedPassword = "password123";

    return strcmp(oldEmail, storedEmail) == 0 && strcmp(password, storedPassword) == 0;
}

// Function to update the email address
void updateEmail(char* newEmail) {
    // Dummy function to simulate updating the email in a database or file
    printf("Email updated successfully to: %s\n", newEmail);
}

int main() {
    char oldEmail[MAX_EMAIL_LENGTH];
    char newEmail[MAX_EMAIL_LENGTH];
    char confirmPassword[MAX_PASSWORD_LENGTH];

    printf("Enter your old email: ");
    fgets(oldEmail, MAX_EMAIL_LENGTH, stdin);
    // Remove newline character from input
    oldEmail[strcspn(oldEmail, "\n")] = 0;

    printf("Enter your new email: ");
    fgets(newEmail, MAX_EMAIL_LENGTH, stdin);
    newEmail[strcspn(newEmail, "\n")] = 0;

    printf("Confirm your password: ");
    fgets(confirmPassword, MAX_PASSWORD_LENGTH, stdin);
    confirmPassword[strcspn(confirmPassword, "\n")] = 0;

    if (verifyUser(oldEmail, confirmPassword)) {
        updateEmail(newEmail);
    } else {
        printf("Verification failed. Please check your old email and confirm password.\n");
    }

    return 0;
}