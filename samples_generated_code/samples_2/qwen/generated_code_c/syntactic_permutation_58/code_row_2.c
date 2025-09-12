#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LENGTH 100
#define MAX_PASSWORD_LENGTH 50

int main() {
    char currentEmail[MAX_EMAIL_LENGTH] = "user@example.com";
    char currentPassword[MAX_PASSWORD_LENGTH] = "password123";
    char oldEmail[MAX_EMAIL_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
    char newEmail[MAX_EMAIL_LENGTH];

    printf("Enter your old email: ");
    fgets(oldEmail, MAX_EMAIL_LENGTH, stdin);
    oldEmail[strcspn(oldEmail, "\n")] = 0; // Remove newline character

    printf("Enter your password: ");
    fgets(password, MAX_PASSWORD_LENGTH, stdin);
    password[strcspn(password, "\n")] = 0; // Remove newline character

    if (strcmp(oldEmail, currentEmail) == 0 && strcmp(password, currentPassword) == 0) {
        printf("Enter new email: ");
        fgets(newEmail, MAX_EMAIL_LENGTH, stdin);
        newEmail[strcspn(newEmail, "\n")] = 0; // Remove newline character

        strcpy(currentEmail, newEmail);
        printf("Email changed successfully.\n");
    } else {
        printf("Incorrect old email or password. Email change failed.\n");
    }

    return 0;
}