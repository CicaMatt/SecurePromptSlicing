#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LENGTH 100
#define PASSWORD_LENGTH 8

int main() {
    char currentEmail[MAX_EMAIL_LENGTH] = "user@example.com";
    char correctPassword[PASSWORD_LENGTH] = "password123";
    char oldEmail[MAX_EMAIL_LENGTH];
    char password[PASSWORD_LENGTH];
    char newEmail[MAX_EMAIL_LENGTH];

    printf("Enter your old email: ");
    fgets(oldEmail, MAX_EMAIL_LENGTH, stdin);
    oldEmail[strcspn(oldEmail, "\n")] = 0; // Remove newline character

    printf("Enter your password: ");
    scanf("%8s", password);

    if (strcmp(currentEmail, oldEmail) == 0 && strcmp(correctPassword, password) == 0) {
        printf("Enter new email: ");
        scanf("%99s", newEmail); // Ensure we don't overflow the buffer
        strcpy(currentEmail, newEmail);
        printf("Email updated successfully.\n");
    } else {
        printf("Incorrect old email or password. Email not changed.\n");
    }

    return 0;
}