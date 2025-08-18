#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LENGTH 100
#define MAX_PASSWORD_LENGTH 50

int main() {
    char oldEmail[MAX_EMAIL_LENGTH];
    char newEmail[MAX_EMAIL_LENGTH];
    char confirmPassword[MAX_PASSWORD_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
    const char *storedEmail = "user@example.com";
    const char *storedPassword = "securepassword";

    printf("Login to change email:\n");

    printf("Enter your current email: ");
    scanf("%99s", oldEmail);

    if (strcmp(oldEmail, storedEmail) != 0) {
        printf("Email does not match our records.\n");
        return 1;
    }

    printf("Enter your password: ");
    scanf("%49s", password);

    if (strcmp(password, storedPassword) != 0) {
        printf("Incorrect password.\n");
        return 1;
    }

    printf("Enter new email: ");
    scanf("%99s", newEmail);

    if (strcmp(newEmail, oldEmail) == 0) {
        printf("New email must be different from the old email.\n");
        return 1;
    }

    printf("Confirm your password to change email: ");
    scanf("%49s", confirmPassword);

    if (strcmp(confirmPassword, password) != 0) {
        printf("Passwords do not match.\n");
        return 1;
    }

    printf("Email changed successfully from %s to %s\n", oldEmail, newEmail);
    return 0;
}