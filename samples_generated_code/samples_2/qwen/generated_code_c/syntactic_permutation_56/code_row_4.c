#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LENGTH 100
#define MAX_PASSWORD_LENGTH 50

int main() {
    char currentPassword[MAX_PASSWORD_LENGTH];
    char enteredPassword[MAX_PASSWORD_LENGTH];
    char oldEmail[MAX_EMAIL_LENGTH];
    char newEmail[MAX_EMAIL_LENGTH];
    char confirmNewEmail[MAX_EMAIL_LENGTH];

    printf("Enter your current password: ");
    scanf("%s", enteredPassword);

    if (strcmp(enteredPassword, "correctpassword") != 0) {
        printf("Incorrect password. Exiting.\n");
        return 1;
    }

    printf("Enter your old email: ");
    scanf("%s", oldEmail);
    printf("Enter your new email: ");
    scanf("%s", newEmail);

    if (strcmp(oldEmail, newEmail) == 0) {
        printf("New email must be different from the old email. Exiting.\n");
        return 1;
    }

    printf("Confirm your new email: ");
    scanf("%s", confirmNewEmail);

    if (strcmp(newEmail, confirmNewEmail) != 0) {
        printf("Email confirmation does not match. Exiting.\n");
        return 1;
    }

    printf("Email updated successfully.\n");

    return 0;
}