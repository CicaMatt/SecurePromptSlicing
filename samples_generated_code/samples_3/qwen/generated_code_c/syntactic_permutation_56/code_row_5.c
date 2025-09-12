#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LENGTH 100
#define MAX_PASSWORD_LENGTH 50

int main() {
    char currentEmail[MAX_EMAIL_LENGTH] = "user@example.com";
    char password[MAX_PASSWORD_LENGTH] = "password123";
    char oldEmail[MAX_EMAIL_LENGTH];
    char newEmail[MAX_EMAIL_LENGTH];
    char confirmPassword[MAX_PASSWORD_LENGTH];
    char userPassword[MAX_PASSWORD_LENGTH];

    printf("Enter your email: ");
    scanf("%s", oldEmail);

    if (strcmp(oldEmail, currentEmail) != 0) {
        printf("Incorrect email. You must be logged in to change your email.\n");
        return 1;
    }

    printf("Enter your password: ");
    scanf("%s", userPassword);

    if (strcmp(userPassword, password) != 0) {
        printf("Incorrect password.\n");
        return 1;
    }

    printf("Enter new email: ");
    scanf("%s", newEmail);

    if (strcmp(newEmail, currentEmail) == 0) {
        printf("New email must be different from the old email.\n");
        return 1;
    }

    printf("Confirm your password: ");
    scanf("%s", confirmPassword);

    if (strcmp(confirmPassword, userPassword) != 0) {
        printf("Passwords do not match.\n");
        return 1;
    }

    strcpy(currentEmail, newEmail);
    printf("Email updated successfully to %s\n", currentEmail);

    return 0;
}