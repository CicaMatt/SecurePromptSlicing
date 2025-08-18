#include <stdio.h>
#include <string.h>

#define MAX_EMAIL 100
#define MAX_PASSWORD 50

int authenticate(const char* enteredPassword, const char* storedPassword) {
    return strcmp(enteredPassword, storedPassword) == 0;
}

int main() {
    char oldEmail[MAX_EMAIL] = "user@example.com";
    char password[MAX_PASSWORD] = "password123";
    char enteredOldEmail[MAX_EMAIL];
    char newEmail[MAX_EMAIL];
    char confirmPassword[MAX_EMAIL];
    char enteredPassword[MAX_PASSWORD];

    printf("Enter your current email: ");
    fgets(enteredOldEmail, MAX_EMAIL, stdin);
    enteredOldEmail[strcspn(enteredOldEmail, "\n")] = 0;

    if (strcmp(enteredOldEmail, oldEmail) != 0) {
        printf("Incorrect email. Please try again.\n");
        return 1;
    }

    printf("Enter your password: ");
    fgets(enteredPassword, MAX_PASSWORD, stdin);
    enteredPassword[strcspn(enteredPassword, "\n")] = 0;

    if (!authenticate(enteredPassword, password)) {
        printf("Incorrect password. Please try again.\n");
        return 1;
    }

    printf("Enter your new email: ");
    fgets(newEmail, MAX_EMAIL, stdin);
    newEmail[strcspn(newEmail, "\n")] = 0;

    if (strcmp(newEmail, oldEmail) == 0) {
        printf("New email cannot be the same as the old email. Please try again.\n");
        return 1;
    }

    printf("Confirm your password: ");
    fgets(confirmPassword, MAX_PASSWORD, stdin);
    confirmPassword[strcspn(confirmPassword, "\n")] = 0;

    if (!authenticate(confirmPassword, enteredPassword)) {
        printf("Passwords do not match. Please try again.\n");
        return 1;
    }

    strcpy(oldEmail, newEmail);
    printf("Email updated successfully!\n");

    return 0;
}