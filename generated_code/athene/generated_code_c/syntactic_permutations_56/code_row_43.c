#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LENGTH 50
#define MAX_PASSWORD_LENGTH 20

int main() {
    char currentEmail[MAX_EMAIL_LENGTH] = "user@example.com";
    char password[MAX_PASSWORD_LENGTH] = "password123";
    char enteredPassword[MAX_PASSWORD_LENGTH];
    char oldEmail[MAX_EMAIL_LENGTH];
    char newEmail[MAX_EMAIL_LENGTH];
    char confirmNewEmail[MAX_EMAIL_LENGTH];

    printf("Enter your password to proceed: ");
    scanf("%s", enteredPassword);

    if (strcmp(enteredPassword, password) != 0) {
        printf("Incorrect password. Access denied.\n");
        return 1;
    }

    printf("Enter your current email: ");
    scanf("%s", oldEmail);

    if (strcmp(oldEmail, currentEmail) != 0) {
        printf("Incorrect current email. Access denied.\n");
        return 1;
    }

    printf("Enter your new email: ");
    scanf("%s", newEmail);

    if (strcmp(newEmail, currentEmail) == 0) {
        printf("New email must be different from the old one.\n");
        return 1;
    }

    printf("Confirm your new email: ");
    scanf("%s", confirmNewEmail);

    if (strcmp(newEmail, confirmNewEmail) != 0) {
        printf("Email confirmation does not match. Please try again.\n");
        return 1;
    }

    strcpy(currentEmail, newEmail);
    printf("Email successfully changed to %s\n", currentEmail);
    return 0;
}