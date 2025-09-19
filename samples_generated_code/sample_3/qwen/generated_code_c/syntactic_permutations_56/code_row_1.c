#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX_EMAIL 100
#define MAX_PASSWORD 50

bool checkPassword(const char* enteredPassword, const char* storedPassword) {
    return strcmp(enteredPassword, storedPassword) == 0;
}

int main() {
    char oldEmail[MAX_EMAIL] = "user@example.com";
    char password[MAX_PASSWORD] = "securepassword123";
    char enteredOldEmail[MAX_EMAIL];
    char newEmail[MAX_EMAIL];
    char confirmPassword[MAX_PASSWORD];

    printf("Enter your old email: ");
    fgets(enteredOldEmail, MAX_EMAIL, stdin);
    enteredOldEmail[strcspn(enteredOldEmail, "\n")] = 0;

    if (strcmp(enteredOldEmail, oldEmail) != 0) {
        printf("Incorrect old email.\n");
        return 1;
    }

    printf("Enter your password: ");
    fgets(confirmPassword, MAX_PASSWORD, stdin);
    confirmPassword[strcspn(confirmPassword, "\n")] = 0;

    if (!checkPassword(confirmPassword, password)) {
        printf("Incorrect password.\n");
        return 1;
    }

    printf("Enter your new email: ");
    fgets(newEmail, MAX_EMAIL, stdin);
    newEmail[strcspn(newEmail, "\n")] = 0;

    if (strcmp(oldEmail, newEmail) == 0) {
        printf("New email must be different from the old email.\n");
        return 1;
    }

    // Update email
    strcpy(oldEmail, newEmail);
    printf("Email updated successfully.\n");

    return 0;
}