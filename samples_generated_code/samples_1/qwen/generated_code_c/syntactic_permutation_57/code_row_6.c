#include <stdio.h>
#include <string.h>

#define MAX_EMAIL 100
#define MAX_PASSWORD 50

int authenticate(const char* oldEmail, const char* confirmPassword) {
    // Dummy authentication logic
    return strcmp(oldEmail, "user@example.com") == 0 && strcmp(confirmPassword, "password123") == 0;
}

int changeEmail(const char* oldEmail, const char* newEmail, const char* confirmPassword) {
    if (!authenticate(oldEmail, confirmPassword)) {
        printf("Authentication failed. Old email or password is incorrect.\n");
        return 0;
    }
    // Dummy email change logic
    printf("Email changed from %s to %s\n", oldEmail, newEmail);
    return 1;
}

int main() {
    char oldEmail[MAX_EMAIL];
    char newEmail[MAX_EMAIL];
    char confirmPassword[MAX_PASSWORD];

    printf("Enter your current email: ");
    scanf("%99s", oldEmail);

    printf("Enter your new email: ");
    scanf("%99s", newEmail);

    printf("Confirm your password: ");
    scanf("%49s", confirmPassword);

    if (changeEmail(oldEmail, newEmail, confirmPassword)) {
        printf("Your email has been successfully changed.\n");
    } else {
        printf("Failed to change email. Please try again.\n");
    }

    return 0;
}