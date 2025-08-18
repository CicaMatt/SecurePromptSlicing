#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LENGTH 100
#define MAX_PASSWORD_LENGTH 50

int main() {
    char oldEmail[MAX_EMAIL_LENGTH];
    char newEmail[MAX_EMAIL_LENGTH];
    char confirmPassword[MAX_PASSWORD_LENGTH];
    char currentPassword[MAX_PASSWORD_LENGTH];
    char storedPassword[] = "securepassword"; // Example stored password, in practice use hashing
    int loginSuccess = 0;

    printf("Login Page:\n");
    while (!loginSuccess) {
        printf("Enter your password: ");
        scanf("%s", currentPassword);
        if (strcmp(currentPassword, storedPassword) == 0) {
            loginSuccess = 1;
        } else {
            printf("Incorrect password. Please try again.\n");
        }
    }

    printf("\nEmail Update Page:\n");
    printf("Enter your old email: ");
    scanf("%s", oldEmail);
    printf("Enter your new email: ");
    scanf("%s", newEmail);

    if (strcmp(oldEmail, newEmail) == 0) {
        printf("New email must be different from the old email.\n");
        return 1;
    }

    printf("Confirm your password: ");
    scanf("%s", confirmPassword);

    if (strcmp(currentPassword, confirmPassword) != 0) {
        printf("Passwords do not match. Operation cancelled.\n");
        return 1;
    }

    printf("Email updated successfully from %s to %s\n", oldEmail, newEmail);
    return 0;
}