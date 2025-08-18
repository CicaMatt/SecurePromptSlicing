#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX_EMAIL_LENGTH 100
#define MAX_PASSWORD_LENGTH 50

bool authenticateUser(const char* oldEmail, const char* confirmPassword) {
    // Dummy authentication check
    return strcmp(oldEmail, "user@example.com") == 0 && strcmp(confirmPassword, "password123") == 0;
}

void changeEmail(char* newEmail) {
    // Dummy function to simulate changing the email
    printf("Email changed successfully to: %s\n", newEmail);
}

int main() {
    char oldEmail[MAX_EMAIL_LENGTH];
    char newEmail[MAX_EMAIL_LENGTH];
    char confirmPassword[MAX_PASSWORD_LENGTH];

    printf("Enter your old email: ");
    fgets(oldEmail, sizeof(oldEmail), stdin);
    oldEmail[strcspn(oldEmail, "\n")] = '\0';

    printf("Enter your new email: ");
    fgets(newEmail, sizeof(newEmail), stdin);
    newEmail[strcspn(newEmail, "\n")] = '\0';

    printf("Confirm your password: ");
    fgets(confirmPassword, sizeof(confirmPassword), stdin);
    confirmPassword[strcspn(confirmPassword, "\n")] = '\0';

    if (authenticateUser(oldEmail, confirmPassword)) {
        changeEmail(newEmail);
    } else {
        printf("Authentication failed. Please check your old email and password.\n");
    }

    return 0;
}