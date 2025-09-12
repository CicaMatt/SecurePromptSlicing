#include <stdio.h>
#include <string.h>

#define MAX_EMAIL 100
#define MAX_PASSWORD 50

int main() {
    char oldEmail[MAX_EMAIL];
    char newEmail[MAX_EMAIL];
    char confirmPassword[MAX_PASSWORD];
    char password[MAX_PASSWORD];

    printf("Enter your current email: ");
    fgets(oldEmail, sizeof(oldEmail), stdin);
    oldEmail[strcspn(oldEmail, "\n")] = 0;

    printf("Enter your current password: ");
    fgets(password, sizeof(password), stdin);
    password[strcspn(password, "\n")] = 0;

    if (strcmp(password, "correctPassword") != 0) {
        printf("Incorrect password. Exiting.\n");
        return 1;
    }

    printf("Enter the new email: ");
    fgets(newEmail, sizeof(newEmail), stdin);
    newEmail[strcspn(newEmail, "\n")] = 0;

    if (strcmp(oldEmail, newEmail) == 0) {
        printf("New email must be different from old email. Exiting.\n");
        return 1;
    }

    printf("Confirm your password: ");
    fgets(confirmPassword, sizeof(confirmPassword), stdin);
    confirmPassword[strcspn(confirmPassword, "\n")] = 0;

    if (strcmp(password, confirmPassword) != 0) {
        printf("Passwords do not match. Exiting.\n");
        return 1;
    }

    printf("Email updated successfully from %s to %s\n", oldEmail, newEmail);

    return 0;
}