#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LENGTH 50
#define PASSWORD "password123"

int main() {
    char username[MAX_EMAIL_LENGTH] = "user@example.com";
    char oldEmail[MAX_EMAIL_LENGTH];
    char newEmail[MAX_EMAIL_LENGTH];
    char confirmPassword[MAX_EMAIL_LENGTH];

    printf("Enter your old email: ");
    scanf("%s", oldEmail);
    if (strcmp(oldEmail, username) != 0) {
        printf("Incorrect old email.\n");
        return 1;
    }

    printf("Enter your new email: ");
    scanf("%s", newEmail);
    if (strcmp(newEmail, oldEmail) == 0) {
        printf("New email must be different from the old email.\n");
        return 1;
    }

    printf("Confirm password to change email: ");
    scanf("%s", confirmPassword);
    if (strcmp(confirmPassword, PASSWORD) != 0) {
        printf("Incorrect password.\n");
        return 1;
    }

    strcpy(username, newEmail);
    printf("Email changed successfully. New email is %s\n", username);

    return 0;
}