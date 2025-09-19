#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LENGTH 50
#define MAX_PASSWORD_LENGTH 20

int main() {
    char oldEmail[MAX_EMAIL_LENGTH];
    char newEmail[MAX_EMAIL_LENGTH];
    char confirmNewEmail[MAX_EMAIL_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
    char storedPassword[] = "securepassword123"; // Example stored password
    char storedEmail[] = "user@example.com";     // Example stored email

    printf("Enter your current email: ");
    fgets(oldEmail, MAX_EMAIL_LENGTH, stdin);
    oldEmail[strcspn(oldEmail, "\n")] = 0; // Remove newline character

    if (strcmp(oldEmail, storedEmail) != 0) {
        printf("Incorrect email. Please log in with the correct email.\n");
        return 1;
    }

    printf("Enter your password: ");
    fgets(password, MAX_PASSWORD_LENGTH, stdin);
    password[strcspn(password, "\n")] = 0; // Remove newline character

    if (strcmp(password, storedPassword) != 0) {
        printf("Incorrect password. Please try again.\n");
        return 1;
    }

    printf("Enter your new email: ");
    fgets(newEmail, MAX_EMAIL_LENGTH, stdin);
    newEmail[strcspn(newEmail, "\n")] = 0; // Remove newline character

    if (strcmp(newEmail, oldEmail) == 0) {
        printf("New email must be different from the old email.\n");
        return 1;
    }

    printf("Confirm your new email: ");
    fgets(confirmNewEmail, MAX_EMAIL_LENGTH, stdin);
    confirmNewEmail[strcspn(confirmNewEmail, "\n")] = 0; // Remove newline character

    if (strcmp(newEmail, confirmNewEmail) != 0) {
        printf("The emails do not match. Please try again.\n");
        return 1;
    }

    strcpy(storedEmail, newEmail);
    printf("Email updated successfully!\n");

    return 0;
}