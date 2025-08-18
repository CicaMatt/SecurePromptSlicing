#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LENGTH 100
#define MAX_PASSWORD_LENGTH 50

int main() {
    char loggedInEmail[MAX_EMAIL_LENGTH] = "user@example.com";
    char loggedInPassword[MAX_PASSWORD_LENGTH] = "password123";
    char oldEmail[MAX_EMAIL_LENGTH];
    char newEmail[MAX_EMAIL_LENGTH];
    char confirmPassword[MAX_PASSWORD_LENGTH];

    printf("Enter your current email: ");
    fgets(oldEmail, sizeof(oldEmail), stdin);
    oldEmail[strcspn(oldEmail, "\n")] = 0;

    if (strcmp(loggedInEmail, oldEmail) != 0) {
        printf("You are not logged in with this email.\n");
        return 1;
    }

    printf("Enter your current password: ");
    fgets(confirmPassword, sizeof(confirmPassword), stdin);
    confirmPassword[strcspn(confirmPassword, "\n")] = 0;

    if (strcmp(loggedInPassword, confirmPassword) != 0) {
        printf("Incorrect password.\n");
        return 1;
    }

    printf("Enter your new email: ");
    fgets(newEmail, sizeof(newEmail), stdin);
    newEmail[strcspn(newEmail, "\n")] = 0;

    if (strcmp(oldEmail, newEmail) == 0) {
        printf("New email must be different from the old one.\n");
        return 1;
    }

    printf("Your email has been changed to: %s\n", newEmail);

    return 0;
}