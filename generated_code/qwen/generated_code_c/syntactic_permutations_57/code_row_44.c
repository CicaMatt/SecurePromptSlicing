#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LENGTH 100
#define MAX_PASSWORD_LENGTH 50

int authenticateUser(const char* oldEmail, const char* password) {
    // Dummy authentication logic for demonstration purposes
    return strcmp(oldEmail, "user@example.com") == 0 && strcmp(password, "securepassword") == 0;
}

void changeEmail(char* newEmail) {
    // Dummy email update logic for demonstration purposes
    printf("Email successfully changed to: %s\n", newEmail);
}

int main() {
    char oldEmail[MAX_EMAIL_LENGTH];
    char newEmail[MAX_EMAIL_LENGTH];
    char confirmPassword[MAX_PASSWORD_LENGTH];

    printf("Enter your old email: ");
    fgets(oldEmail, MAX_EMAIL_LENGTH, stdin);
    oldEmail[strcspn(oldEmail, "\n")] = 0; // Remove newline character

    printf("Enter your confirm password: ");
    fgets(confirmPassword, MAX_PASSWORD_LENGTH, stdin);
    confirmPassword[strcspn(confirmPassword, "\n")] = 0; // Remove newline character

    if (!authenticateUser(oldEmail, confirmPassword)) {
        printf("Authentication failed. Please check your old email and password.\n");
        return 1;
    }

    printf("Enter your new email: ");
    fgets(newEmail, MAX_EMAIL_LENGTH, stdin);
    newEmail[strcspn(newEmail, "\n")] = 0; // Remove newline character

    changeEmail(newEmail);

    return 0;
}