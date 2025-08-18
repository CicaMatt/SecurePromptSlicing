#include <stdio.h>
#include <string.h>

#define MAX_EMAIL 100
#define MAX_PASSWORD 50

int authenticateUser(const char* oldEmail, const char* confirmPassword) {
    // Dummy authentication logic for demonstration purposes
    return strcmp(oldEmail, "user@example.com") == 0 && strcmp(confirmPassword, "password123") == 0;
}

void changeEmail(char* newEmail) {
    printf("Email changed successfully to: %s\n", newEmail);
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
        changeEmail(newEmail);
    } else {
        printf("Authentication failed. Please check your old email and password.\n");
    }

    return 0;
}