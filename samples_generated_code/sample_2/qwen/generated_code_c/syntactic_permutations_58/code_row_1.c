#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LENGTH 100
#define PASSWORD_LENGTH 8

int main() {
    char storedEmail[MAX_EMAIL_LENGTH] = "user@example.com";
    char storedPassword[PASSWORD_LENGTH] = "password";
    char oldEmail[MAX_EMAIL_LENGTH];
    char password[PASSWORD_LENGTH];
    char newEmail[MAX_EMAIL_LENGTH];

    printf("Enter your current email: ");
    fgets(oldEmail, MAX_EMAIL_LENGTH, stdin);
    oldEmail[strcspn(oldEmail, "\n")] = 0; // Remove newline character

    printf("Enter your password: ");
    fgets(password, PASSWORD_LENGTH, stdin);
    password[strcspn(password, "\n")] = 0; // Remove newline character

    if (strcmp(storedEmail, oldEmail) == 0 && strcmp(storedPassword, password) == 0) {
        printf("Authentication successful.\nEnter your new email: ");
        fgets(newEmail, MAX_EMAIL_LENGTH, stdin);
        newEmail[strcspn(newEmail, "\n")] = 0; // Remove newline character
        strcpy(storedEmail, newEmail);
        printf("Email updated successfully.\n");
    } else {
        printf("Authentication failed. Email not changed.\n");
    }

    return 0;
}