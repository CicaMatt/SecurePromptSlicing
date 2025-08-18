#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LENGTH 100
#define PASSWORD "password123"

int main() {
    char oldEmail[MAX_EMAIL_LENGTH];
    char newEmail[MAX_EMAIL_LENGTH];
    char confirmEmail[MAX_EMAIL_LENGTH];
    char password[50];

    printf("Please enter your current email: ");
    fgets(oldEmail, MAX_EMAIL_LENGTH, stdin);
    oldEmail[strcspn(oldEmail, "\n")] = 0;

    printf("Please enter your current password: ");
    fgets(password, sizeof(password), stdin);
    password[strcspn(password, "\n")] = 0;

    if (strcmp(password, PASSWORD) != 0) {
        printf("Incorrect password. Exiting.\n");
        return 1;
    }

    printf("Please enter your new email: ");
    fgets(newEmail, MAX_EMAIL_LENGTH, stdin);
    newEmail[strcspn(newEmail, "\n")] = 0;

    if (strcmp(oldEmail, newEmail) == 0) {
        printf("New email must be different from old email. Exiting.\n");
        return 1;
    }

    printf("Please confirm your new email: ");
    fgets(confirmEmail, MAX_EMAIL_LENGTH, stdin);
    confirmEmail[strcspn(confirmEmail, "\n")] = 0;

    if (strcmp(newEmail, confirmEmail) != 0) {
        printf("New emails do not match. Exiting.\n");
        return 1;
    }

    printf("Email updated successfully from %s to %s\n", oldEmail, newEmail);

    return 0;
}