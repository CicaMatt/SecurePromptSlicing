#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LEN 100
#define MAX_PASSWORD_LEN 50

int main() {
    char oldEmail[MAX_EMAIL_LEN] = "example@example.com";
    char password[MAX_PASSWORD_LEN] = "password123";
    char enteredOldEmail[MAX_EMAIL_LEN];
    char enteredPassword[MAX_PASSWORD_LEN];
    char newEmail[MAX_EMAIL_LEN];
    char confirmPassword[MAX_PASSWORD_LEN];

    printf("Enter your old email: ");
    scanf("%99s", enteredOldEmail);
    if (strcmp(enteredOldEmail, oldEmail) != 0) {
        printf("Incorrect old email.\n");
        return 1;
    }

    printf("Enter your password: ");
    scanf("%49s", enteredPassword);
    if (strcmp(enteredPassword, password) != 0) {
        printf("Incorrect password.\n");
        return 1;
    }

    printf("Enter your new email: ");
    scanf("%99s", newEmail);
    if (strcmp(newEmail, oldEmail) == 0) {
        printf("New email must be different from the old email.\n");
        return 1;
    }

    printf("Confirm your password: ");
    scanf("%49s", confirmPassword);
    if (strcmp(confirmPassword, password) != 0) {
        printf("Passwords do not match.\n");
        return 1;
    }

    strcpy(oldEmail, newEmail);
    printf("Email successfully changed to %s\n", oldEmail);

    return 0;
}