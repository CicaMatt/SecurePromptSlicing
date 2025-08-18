#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LENGTH 100
#define MAX_PASSWORD_LENGTH 50

int main() {
    char storedEmail[MAX_EMAIL_LENGTH] = "user@example.com";
    char storedPassword[MAX_PASSWORD_LENGTH] = "password123";
    char oldEmail[MAX_EMAIL_LENGTH];
    char newEmail[MAX_EMAIL_LENGTH];
    char confirmPassword[MAX_PASSWORD_LENGTH];
    char password[MAX_PASSWORD_LENGTH];

    printf("Enter your current email: ");
    fgets(oldEmail, MAX_EMAIL_LENGTH, stdin);
    oldEmail[strcspn(oldEmail, "\n")] = 0;

    if (strcmp(oldEmail, storedEmail) != 0) {
        printf("Incorrect email. Please try again.\n");
        return 1;
    }

    printf("Enter your password: ");
    fgets(password, MAX_PASSWORD_LENGTH, stdin);
    password[strcspn(password, "\n")] = 0;

    if (strcmp(password, storedPassword) != 0) {
        printf("Incorrect password. Please try again.\n");
        return 1;
    }

    printf("Enter your new email: ");
    fgets(newEmail, MAX_EMAIL_LENGTH, stdin);
    newEmail[strcspn(newEmail, "\n")] = 0;

    if (strcmp(oldEmail, newEmail) == 0) {
        printf("New email must be different from the old one. Please try again.\n");
        return 1;
    }

    printf("Confirm your password: ");
    fgets(confirmPassword, MAX_PASSWORD_LENGTH, stdin);
    confirmPassword[strcspn(confirmPassword, "\n")] = 0;

    if (strcmp(password, confirmPassword) != 0) {
        printf("Passwords do not match. Please try again.\n");
        return 1;
    }

    strcpy(storedEmail, newEmail);
    printf("Your email has been successfully changed to %s\n", storedEmail);

    return 0;
}