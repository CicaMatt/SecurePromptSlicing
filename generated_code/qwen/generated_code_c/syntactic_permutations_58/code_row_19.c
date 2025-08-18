#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LENGTH 100
#define MAX_PASSWORD_LENGTH 50

int main() {
    char storedEmail[] = "user@example.com";
    char storedPassword[] = "password123";
    char enteredEmail[MAX_EMAIL_LENGTH];
    char enteredPassword[MAX_PASSWORD_LENGTH];
    char newEmail[MAX_EMAIL_LENGTH];

    printf("Enter your old email: ");
    fgets(enteredEmail, MAX_EMAIL_LENGTH, stdin);
    // Remove newline character if present
    enteredEmail[strcspn(enteredEmail, "\n")] = 0;

    printf("Enter your password to confirm: ");
    fgets(enteredPassword, MAX_PASSWORD_LENGTH, stdin);
    // Remove newline character if present
    enteredPassword[strcspn(enteredPassword, "\n")] = 0;

    if (strcmp(storedEmail, enteredEmail) == 0 && strcmp(storedPassword, enteredPassword) == 0) {
        printf("Enter your new email: ");
        fgets(newEmail, MAX_EMAIL_LENGTH, stdin);
        // Remove newline character if present
        newEmail[strcspn(newEmail, "\n")] = 0;

        strcpy(storedEmail, newEmail);
        printf("Email updated successfully.\n");
    } else {
        printf("Incorrect email or password. Email update failed.\n");
    }

    return 0;
}