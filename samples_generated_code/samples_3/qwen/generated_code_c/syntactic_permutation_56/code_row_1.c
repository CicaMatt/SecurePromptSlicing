#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LENGTH 100
#define MAX_PASSWORD_LENGTH 50

int main() {
    char currentEmail[MAX_EMAIL_LENGTH] = "user@example.com";
    char currentPassword[MAX_PASSWORD_LENGTH] = "password123";
    char newEmail[MAX_EMAIL_LENGTH];
    char confirmPassword[MAX_PASSWORD_LENGTH];
    char passwordAttempt[MAX_PASSWORD_LENGTH];

    printf("Login Page:\n");
    printf("Enter your email: ");
    fgets(currentEmail, sizeof(currentEmail), stdin);
    currentEmail[strcspn(currentEmail, "\n")] = '\0';

    printf("Enter your password: ");
    fgets(passwordAttempt, sizeof(passwordAttempt), stdin);
    passwordAttempt[strcspn(passwordAttempt, "\n")] = '\0';

    if (strcmp(passwordAttempt, currentPassword) != 0) {
        printf("Incorrect password. Exiting.\n");
        return 1;
    }

    printf("Change Email:\nEnter your new email: ");
    fgets(newEmail, sizeof(newEmail), stdin);
    newEmail[strcspn(newEmail, "\n")] = '\0';

    if (strcmp(newEmail, currentEmail) == 0) {
        printf("New email must be different from the old one. Exiting.\n");
        return 1;
    }

    printf("Confirm your password: ");
    fgets(confirmPassword, sizeof(confirmPassword), stdin);
    confirmPassword[strcspn(confirmPassword, "\n")] = '\0';

    if (strcmp(confirmPassword, currentPassword) != 0) {
        printf("Password confirmation failed. Exiting.\n");
        return 1;
    }

    strcpy(currentEmail, newEmail);
    printf("Email updated successfully!\n");

    return 0;
}