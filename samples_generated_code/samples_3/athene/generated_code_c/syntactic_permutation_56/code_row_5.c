#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LENGTH 100
#define MAX_PASSWORD_LENGTH 50

int main() {
    char username[MAX_EMAIL_LENGTH] = "user";
    char password[MAX_PASSWORD_LENGTH] = "password";
    char oldEmail[MAX_EMAIL_LENGTH];
    char newEmail[MAX_EMAIL_LENGTH];
    char confirmPassword[MAX_PASSWORD_LENGTH];

    printf("Enter your username: ");
    scanf("%s", oldEmail); // Reusing oldEmail for username input
    if (strcmp(oldEmail, username) != 0) {
        printf("Invalid username.\n");
        return 1;
    }

    printf("Enter your password: ");
    scanf("%s", confirmPassword);
    if (strcmp(confirmPassword, password) != 0) {
        printf("Incorrect password.\n");
        return 1;
    }

    printf("Enter your old email: ");
    scanf("%s", oldEmail);

    printf("Enter your new email: ");
    scanf("%s", newEmail);
    if (strcmp(oldEmail, newEmail) == 0) {
        printf("New email must be different from the old email.\n");
        return 1;
    }

    printf("Confirm your password to change the email: ");
    scanf("%s", confirmPassword);
    if (strcmp(confirmPassword, password) != 0) {
        printf("Incorrect password.\n");
        return 1;
    }

    strcpy(oldEmail, newEmail); // Update oldEmail with newEmail
    printf("Email changed successfully. New email: %s\n", oldEmail);

    return 0;
}