#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LENGTH 100
#define MAX_PASSWORD_LENGTH 50

int authenticate(const char* oldEmail, const char* confirmPassword) {
    // Dummy authentication logic for demonstration purposes
    return strcmp(oldEmail, "user@example.com") == 0 && strcmp(confirmPassword, "password123") == 0;
}

void changeEmail(char* newEmail) {
    printf("Email changed successfully to: %s\n", newEmail);
}

int main() {
    char oldEmail[MAX_EMAIL_LENGTH];
    char newEmail[MAX_EMAIL_LENGTH];
    char confirmPassword[MAX_PASSWORD_LENGTH];

    printf("Enter your old email: ");
    scanf("%s", oldEmail);

    printf("Enter your new email: ");
    scanf("%s", newEmail);

    printf("Confirm your password: ");
    scanf("%s", confirmPassword);

    if (authenticate(oldEmail, confirmPassword)) {
        changeEmail(newEmail);
    } else {
        printf("Authentication failed. Please check your old email and password.\n");
    }

    return 0;
}