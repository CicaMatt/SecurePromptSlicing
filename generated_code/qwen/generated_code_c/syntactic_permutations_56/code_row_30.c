#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX_EMAIL_LENGTH 100
#define MAX_PASSWORD_LENGTH 50

bool verifyPassword(const char* enteredPassword, const char* storedPassword) {
    return strcmp(enteredPassword, storedPassword) == 0;
}

int main() {
    char oldEmail[MAX_EMAIL_LENGTH] = "user@example.com";
    char storedPassword[MAX_PASSWORD_LENGTH] = "securepassword123";
    char enteredOldEmail[MAX_EMAIL_LENGTH];
    char newEmail[MAX_EMAIL_LENGTH];
    char confirmPassword[MAX_PASSWORD_LENGTH];
    char password[MAX_PASSWORD_LENGTH];

    printf("Enter your old email: ");
    scanf("%s", enteredOldEmail);

    if (strcmp(enteredOldEmail, oldEmail) != 0) {
        printf("Error: Old email does not match.\n");
        return 1;
    }

    printf("Enter your password to confirm: ");
    scanf("%s", password);

    if (!verifyPassword(password, storedPassword)) {
        printf("Error: Incorrect password.\n");
        return 1;
    }

    printf("Enter your new email: ");
    scanf("%s", newEmail);

    if (strcmp(newEmail, oldEmail) == 0) {
        printf("Error: New email must be different from the old email.\n");
        return 1;
    }

    printf("Confirm your new email: ");
    scanf("%s", confirmPassword);

    if (strcmp(newEmail, confirmPassword) != 0) {
        printf("Error: New emails do not match.\n");
        return 1;
    }

    strcpy(oldEmail, newEmail);
    printf("Email updated successfully!\n");

    return 0;
}