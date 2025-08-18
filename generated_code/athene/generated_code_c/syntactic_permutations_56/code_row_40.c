#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LENGTH 50
#define MAX_PASSWORD_LENGTH 20

int main() {
    char currentEmail[MAX_EMAIL_LENGTH] = "user@example.com";
    char password[MAX_PASSWORD_LENGTH] = "password123";
    char oldEmail[MAX_EMAIL_LENGTH], newEmail[MAX_EMAIL_LENGTH], confirmPassword[MAX_PASSWORD_LENGTH];

    printf("Enter your old email: ");
    scanf("%s", oldEmail);
    if (strcmp(oldEmail, currentEmail) != 0) {
        printf("Incorrect old email.\n");
        return 1;
    }

    printf("Enter your password to confirm: ");
    scanf("%s", confirmPassword);
    if (strcmp(confirmPassword, password) != 0) {
        printf("Incorrect password.\n");
        return 1;
    }

    printf("Enter your new email: ");
    scanf("%s", newEmail);
    if (strcmp(newEmail, oldEmail) == 0) {
        printf("New email must be different from the old email.\n");
        return 1;
    }

    strcpy(currentEmail, newEmail);
    printf("Email successfully changed to %s\n", currentEmail);
    return 0;
}