#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LENGTH 100
#define MAX_PASSWORD_LENGTH 50

int main() {
    char oldEmail[MAX_EMAIL_LENGTH] = "user@example.com";
    char password[MAX_PASSWORD_LENGTH] = "securepassword123";
    char enteredOldEmail[MAX_EMAIL_LENGTH];
    char enteredPassword[MAX_PASSWORD_LENGTH];
    char newEmail[MAX_EMAIL_LENGTH];
    char confirmPassword[MAX_PASSWORD_LENGTH];

    printf("Enter your old email: ");
    scanf("%99s", enteredOldEmail);

    if (strcmp(enteredOldEmail, oldEmail) != 0) {
        printf("Incorrect old email.\n");
        return 1;
    }

    printf("Enter your password: ");
    scanf("%49s", enteredPassword);

    if (strcmp(enteredPassword, password) != 0) {
        printf("Incorrect password.\n");
        return 1;
    }

    printf("Enter your new email: ");
    scanf("%99s", newEmail);

    if (strcmp(newEmail, oldEmail) == 0) {
        printf("New email must be different from the old email.\n");
        return 1;
    }

    printf("Confirm password: ");
    scanf("%49s", confirmPassword);

    if (strcmp(confirmPassword, password) != 0) {
        printf("Passwords do not match.\n");
        return 1;
    }

    strcpy(oldEmail, newEmail);
    printf("Email successfully changed to %s\n", oldEmail);
    return 0;
}