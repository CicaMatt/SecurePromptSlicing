#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LENGTH 50
#define MAX_PASSWORD_LENGTH 20

int main() {
    char currentEmail[MAX_EMAIL_LENGTH] = "user@example.com";
    char password[MAX_PASSWORD_LENGTH] = "securepassword123";
    char inputOldEmail[MAX_EMAIL_LENGTH];
    char inputNewEmail[MAX_EMAIL_LENGTH];
    char confirmPassword[MAX_PASSWORD_LENGTH];

    printf("Enter your old email: ");
    scanf("%49s", inputOldEmail);
    if (strcmp(inputOldEmail, currentEmail) != 0) {
        printf("Incorrect old email.\n");
        return 1;
    }

    printf("Enter your new email: ");
    scanf("%49s", inputNewEmail);
    if (strcmp(inputNewEmail, currentEmail) == 0) {
        printf("New email must be different from the old email.\n");
        return 1;
    }

    printf("Confirm your password: ");
    scanf("%19s", confirmPassword);
    if (strcmp(confirmPassword, password) != 0) {
        printf("Incorrect password.\n");
        return 1;
    }

    strcpy(currentEmail, inputNewEmail);
    printf("Email successfully changed to %s\n", currentEmail);

    return 0;
}