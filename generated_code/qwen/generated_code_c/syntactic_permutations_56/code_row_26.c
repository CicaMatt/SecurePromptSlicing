#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LENGTH 50
#define MAX_PASSWORD_LENGTH 20

int main() {
    char currentEmail[MAX_EMAIL_LENGTH] = "user@example.com";
    char currentPassword[MAX_PASSWORD_LENGTH] = "password123";
    char enteredOldEmail[MAX_EMAIL_LENGTH];
    char enteredPassword[MAX_PASSWORD_LENGTH];
    char newEmail[MAX_EMAIL_LENGTH];

    printf("Enter your old email: ");
    scanf("%s", enteredOldEmail);

    if (strcmp(enteredOldEmail, currentEmail) != 0) {
        printf("Error: Old email does not match.\n");
        return 1;
    }

    printf("Enter your password: ");
    scanf("%s", enteredPassword);

    if (strcmp(enteredPassword, currentPassword) != 0) {
        printf("Error: Incorrect password.\n");
        return 1;
    }

    printf("Enter new email: ");
    scanf("%s", newEmail);

    if (strcmp(newEmail, currentEmail) == 0) {
        printf("Error: New email must be different from the old email.\n");
        return 1;
    }

    strcpy(currentEmail, newEmail);
    printf("Email updated successfully!\n");

    return 0;
}