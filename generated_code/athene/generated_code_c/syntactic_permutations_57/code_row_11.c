#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LEN 50
#define PASSWORD "correctpassword"

int main() {
    char oldEmail[MAX_EMAIL_LEN], newEmail[MAX_EMAIL_LEN], confirmPassword[MAX_EMAIL_LEN];
    int loginAttempts = 3;

    while (loginAttempts > 0) {
        printf("Enter your old email: ");
        scanf("%49s", oldEmail);

        if (strcmp(oldEmail, "user@example.com") == 0) {
            printf("Enter new email: ");
            scanf("%49s", newEmail);
            printf("Confirm password: ");
            scanf("%20s", confirmPassword);

            if (strcmp(confirmPassword, PASSWORD) == 0) {
                printf("Email changed successfully. New email: %s\n", newEmail);
                return 0;
            } else {
                loginAttempts--;
                printf("Incorrect confirm password. %d attempts left.\n", loginAttempts);
            }
        } else {
            loginAttempts--;
            printf("Invalid old email. %d attempts left.\n", loginAttempts);
        }

        if (loginAttempts == 0) {
            printf("Too many failed attempts. Exiting.\n");
            return 1;
        }
    }
    return 0;
}