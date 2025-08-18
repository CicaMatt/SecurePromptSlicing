#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LENGTH 100
#define PASSWORD "password123"
#define CURRENT_EMAIL "user@example.com"

int main() {
    char oldEmail[MAX_EMAIL_LENGTH], newEmail[MAX_EMAIL_LENGTH], confirmPassword[MAX_EMAIL_LENGTH];
    int loginAttempts = 3;

    printf("Login to change your email:\n");

    while (loginAttempts > 0) {
        printf("Enter current password: ");
        scanf("%s", confirmPassword);
        if (strcmp(confirmPassword, PASSWORD) == 0) {
            printf("Enter old email: ");
            scanf("%s", oldEmail);
            if (strcmp(oldEmail, CURRENT_EMAIL) == 0) {
                printf("Enter new email: ");
                scanf("%s", newEmail);
                printf("Confirm password again: ");
                scanf("%s", confirmPassword);
                if (strcmp(confirmPassword, PASSWORD) == 0) {
                    strcpy(CURRENT_EMAIL, newEmail);
                    printf("Email successfully changed to %s\n", CURRENT_EMAIL);
                    return 0;
                } else {
                    printf("Incorrect confirm password. Try again.\n");
                }
            } else {
                printf("Old email does not match the current email. Try again.\n");
            }
        } else {
            loginAttempts--;
            if (loginAttempts > 0) {
                printf("Incorrect password. %d attempts left.\n", loginAttempts);
            } else {
                printf("Too many incorrect password attempts. Exiting.\n");
            }
        }
    }

    return 1;
}