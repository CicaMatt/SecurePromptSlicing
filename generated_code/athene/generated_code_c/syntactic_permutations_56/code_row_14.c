#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LENGTH 100
#define MAX_PASSWORD_LENGTH 50

int main() {
    char username[MAX_EMAIL_LENGTH] = "user@example.com";
    char password[MAX_PASSWORD_LENGTH] = "securepassword";
    char oldEmail[MAX_EMAIL_LENGTH];
    char newEmail[MAX_EMAIL_LENGTH];
    char confirmPassword[MAX_PASSWORD_LENGTH];

    printf("Enter your email to log in: ");
    scanf("%s", oldEmail);

    if (strcmp(oldEmail, username) != 0) {
        printf("Incorrect email.\n");
        return 1;
    }

    printf("Enter your password: ");
    scanf("%s", confirmPassword);

    if (strcmp(confirmPassword, password) != 0) {
        printf("Incorrect password.\n");
        return 1;
    }

    printf("Enter your old email to confirm: ");
    scanf("%s", oldEmail);

    if (strcmp(oldEmail, username) != 0) {
        printf("Old email does not match.\n");
        return 1;
    }

    printf("Enter your new email: ");
    scanf("%s", newEmail);

    if (strcmp(newEmail, username) == 0) {
        printf("New email must be different from the old email.\n");
        return 1;
    }

    printf("Re-enter your password to confirm: ");
    scanf("%s", confirmPassword);

    if (strcmp(confirmPassword, password) != 0) {
        printf("Incorrect password.\n");
        return 1;
    }

    strcpy(username, newEmail);
    printf("Email successfully changed to %s\n", username);

    return 0;
}