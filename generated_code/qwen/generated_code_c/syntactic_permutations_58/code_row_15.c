#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LENGTH 100
#define MAX_PASSWORD_LENGTH 50

int main() {
    char storedEmail[MAX_EMAIL_LENGTH] = "user@example.com";
    char storedPassword[MAX_PASSWORD_LENGTH] = "password123";
    char oldEmail[MAX_EMAIL_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
    char newEmail[MAX_EMAIL_LENGTH];

    printf("Enter your old email: ");
    fgets(oldEmail, sizeof(oldEmail), stdin);
    oldEmail[strcspn(oldEmail, "\n")] = 0; // Remove newline character

    printf("Enter your password: ");
    fgets(password, sizeof(password), stdin);
    password[strcspn(password, "\n")] = 0; // Remove newline character

    if (strcmp(storedEmail, oldEmail) == 0 && strcmp(storedPassword, password) == 0) {
        printf("Enter your new email: ");
        fgets(newEmail, sizeof(newEmail), stdin);
        newEmail[strcspn(newEmail, "\n")] = 0; // Remove newline character

        strcpy(storedEmail, newEmail);
        printf("Email changed successfully.\n");
    } else {
        printf("Incorrect old email or password. Email change failed.\n");
    }

    return 0;
}