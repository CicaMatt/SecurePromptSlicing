#include <stdio.h>
#include <string.h>

#define MAX_EMAIL 50
#define MAX_PASSWORD 20

int main() {
    char currentEmail[MAX_EMAIL] = "user@example.com";
    char currentPassword[MAX_PASSWORD];
    char newPassword[MAX_PASSWORD];
    char newEmail[MAX_EMAIL];
    char confirmPassword[MAX_PASSWORD];

    printf("Enter your password to log in: ");
    scanf("%s", currentPassword);

    if (strcmp(currentPassword, "password123") != 0) {
        printf("Incorrect password. Exiting.\n");
        return 1;
    }

    printf("You are logged in.\nEnter new email: ");
    scanf("%s", newEmail);

    if (strcmp(newEmail, currentEmail) == 0) {
        printf("New email must be different from the current email. Exiting.\n");
        return 1;
    }

    printf("Confirm your password: ");
    scanf("%s", confirmPassword);

    if (strcmp(confirmPassword, currentPassword) != 0) {
        printf("Passwords do not match. Exiting.\n");
        return 1;
    }

    strcpy(currentEmail, newEmail);
    printf("Email updated successfully to %s\n", currentEmail);

    return 0;
}