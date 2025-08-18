#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_EMAIL_LENGTH 100
#define MAX_PASSWORD_LENGTH 50

typedef struct {
    char oldEmail[MAX_EMAIL_LENGTH];
    char newEmail[MAX_EMAIL_LENGTH];
    char confirmPassword[MAX_PASSWORD_LENGTH];
} UserInfo;

int authenticateUser(const char* email, const char* password) {
    // Dummy authentication logic for demonstration purposes
    return strcmp(email, "user@example.com") == 0 && strcmp(password, "correctPassword") == 0;
}

int updateEmail(const char* oldEmail, const char* newEmail) {
    // Dummy email update logic for demonstration purposes
    if (strcmp(oldEmail, "user@example.com") != 0) {
        return 0; // Old email does not match
    }
    printf("Email updated from %s to %s\n", oldEmail, newEmail);
    return 1;
}

int main() {
    UserInfo user;
    char confirmPassword[MAX_PASSWORD_LENGTH];

    printf("Enter your old email: ");
    fgets(user.oldEmail, MAX_EMAIL_LENGTH, stdin);
    user.oldEmail[strcspn(user.oldEmail, "\n")] = '\0'; // Remove newline character

    if (!authenticateUser(user.oldEmail, "correctPassword")) {
        printf("Authentication failed. Please check your email and try again.\n");
        return 1;
    }

    printf("Enter your new email: ");
    fgets(user.newEmail, MAX_EMAIL_LENGTH, stdin);
    user.newEmail[strcspn(user.newEmail, "\n")] = '\0'; // Remove newline character

    printf("Confirm your password: ");
    fgets(confirmPassword, MAX_PASSWORD_LENGTH, stdin);
    confirmPassword[strcspn(confirmPassword, "\n")] = '\0'; // Remove newline character

    if (strcmp(confirmPassword, "correctPassword") != 0) {
        printf("Incorrect password. Please try again.\n");
        return 1;
    }

    if (!updateEmail(user.oldEmail, user.newEmail)) {
        printf("Failed to update email. Please check your old email and try again.\n");
        return 1;
    }

    printf("Email updated successfully.\n");

    return 0;
}