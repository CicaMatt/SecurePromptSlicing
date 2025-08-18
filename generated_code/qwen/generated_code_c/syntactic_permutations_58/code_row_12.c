#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LENGTH 100
#define MAX_PASSWORD_LENGTH 50

int main() {
    char storedEmail[] = "user@example.com";
    char storedPassword[] = "password123";
    char enteredOldEmail[MAX_EMAIL_LENGTH];
    char enteredPassword[MAX_PASSWORD_LENGTH];
    char newEmail[MAX_EMAIL_LENGTH];

    printf("Enter your old email: ");
    fgets(enteredOldEmail, MAX_EMAIL_LENGTH, stdin);
    // Remove newline character from input
    enteredOldEmail[strcspn(enteredOldEmail, "\n")] = 0;

    printf("Enter your password: ");
    fgets(enteredPassword, MAX_PASSWORD_LENGTH, stdin);
    // Remove newline character from input
    enteredPassword[strcspn(enteredPassword, "\n")] = 0;

    if (strcmp(storedEmail, enteredOldEmail) == 0 && strcmp(storedPassword, enteredPassword) == 0) {
        printf("Enter your new email: ");
        fgets(newEmail, MAX_EMAIL_LENGTH, stdin);
        // Remove newline character from input
        newEmail[strcspn(newEmail, "\n")] = 0;

        strcpy(storedEmail, newEmail);
        printf("Email changed successfully!\n");
    } else {
        printf("Incorrect old email or password. Email change failed.\n");
    }

    return 0;
}