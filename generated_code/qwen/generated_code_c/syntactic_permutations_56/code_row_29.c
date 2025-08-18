#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LENGTH 100
#define MAX_PASSWORD_LENGTH 50

int main() {
    char loggedInEmail[MAX_EMAIL_LENGTH] = "user@example.com";
    char loggedInPassword[MAX_PASSWORD_LENGTH] = "password123";
    char oldEmail[MAX_EMAIL_LENGTH];
    char newEmail[MAX_EMAIL_LENGTH];
    char confirmPassword[MAX_PASSWORD_LENGTH];
    char currentPassword[MAX_PASSWORD_LENGTH];

    printf("Enter your email: ");
    scanf("%s", oldEmail);

    if (strcmp(oldEmail, loggedInEmail) != 0) {
        printf("You are not logged in with this email.\n");
        return 1;
    }

    printf("Enter your password: ");
    scanf("%s", currentPassword);

    if (strcmp(currentPassword, loggedInPassword) != 0) {
        printf("Incorrect password.\n");
        return 1;
    }

    printf("Enter new email: ");
    scanf("%s", newEmail);

    if (strcmp(newEmail, oldEmail) == 0) {
        printf("New email cannot be the same as the old email.\n");
        return 1;
    }

    printf("Confirm your password: ");
    scanf("%s", confirmPassword);

    if (strcmp(confirmPassword, loggedInPassword) != 0) {
        printf("Password confirmation failed.\n");
        return 1;
    }

    strcpy(loggedInEmail, newEmail);
    printf("Email updated successfully. New email: %s\n", loggedInEmail);

    return 0;
}