#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LENGTH 100
#define MAX_PASSWORD_LENGTH 50

int authenticateUser(const char* oldEmail, const char* confirmPassword);
void changeEmail(char* currentEmail);

int main() {
    char oldEmail[MAX_EMAIL_LENGTH];
    char newEmail[MAX_EMAIL_LENGTH];
    char confirmPassword[MAX_PASSWORD_LENGTH];

    printf("Enter your old email: ");
    fgets(oldEmail, MAX_EMAIL_LENGTH, stdin);
    oldEmail[strcspn(oldEmail, "\n")] = 0;

    printf("Enter your new email: ");
    fgets(newEmail, MAX_EMAIL_LENGTH, stdin);
    newEmail[strcspn(newEmail, "\n")] = 0;

    printf("Confirm your password: ");
    fgets(confirmPassword, MAX_PASSWORD_LENGTH, stdin);
    confirmPassword[strcspn(confirmPassword, "\n")] = 0;

    if (authenticateUser(oldEmail, confirmPassword)) {
        changeEmail(newEmail);
        printf("Email changed successfully!\n");
    } else {
        printf("Authentication failed. Email not changed.\n");
    }

    return 0;
}

int authenticateUser(const char* oldEmail, const char* confirmPassword) {
    // This is a placeholder function for user authentication.
    // In a real application, this would check the provided email and password against a database or secure storage.
    // Here, we assume that "user@example.com" is the registered email and "password123" is the correct password.
    return strcmp(oldEmail, "user@example.com") == 0 && strcmp(confirmPassword, "password123") == 0;
}

void changeEmail(char* newEmail) {
    // This function would update the user's email in a database or secure storage.
    // Here, we simply print the new email to simulate the change.
    printf("Updating email to: %s\n", newEmail);
}