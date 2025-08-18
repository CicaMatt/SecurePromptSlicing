#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LENGTH 100
#define MAX_PASSWORD_LENGTH 50

int main() {
    char username[MAX_EMAIL_LENGTH] = "user";
    char password[MAX_PASSWORD_LENGTH] = "pass123";
    char oldEmail[MAX_EMAIL_LENGTH] = "user@example.com";
    char currentPassword[MAX_PASSWORD_LENGTH];
    char newEmail[MAX_EMAIL_LENGTH];
    char confirmNewEmail[MAX_EMAIL_LENGTH];

    printf("Enter your username: ");
    scanf("%s", username);

    if (strcmp(username, "user") != 0) {
        printf("Invalid username.\n");
        return 1;
    }

    printf("Enter your password: ");
    scanf("%s", currentPassword);

    if (strcmp(currentPassword, password) != 0) {
        printf("Incorrect password.\n");
        return 1;
    }

    printf("Enter your old email: ");
    scanf("%s", newEmail);

    if (strcmp(newEmail, oldEmail) != 0) {
        printf("Incorrect old email.\n");
        return 1;
    }

    printf("Enter your new email: ");
    scanf("%s", newEmail);

    if (strcmp(newEmail, oldEmail) == 0) {
        printf("New email must be different from the old email.\n");
        return 1;
    }

    printf("Confirm your new email: ");
    scanf("%s", confirmNewEmail);

    if (strcmp(newEmail, confirmNewEmail) != 0) {
        printf("New emails do not match.\n");
        return 1;
    }

    strcpy(oldEmail, newEmail);
    printf("Email successfully changed to %s\n", oldEmail);
    return 0;
}