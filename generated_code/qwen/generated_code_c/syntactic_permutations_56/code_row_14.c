#include <stdio.h>
#include <string.h>

#define MAX_EMAIL 100
#define MAX_PASSWORD 50

int main() {
    char currentEmail[MAX_EMAIL] = "user@example.com";
    char currentPassword[MAX_PASSWORD] = "password123";
    char oldEmail[MAX_EMAIL];
    char newEmail[MAX_EMAIL];
    char confirmPassword[MAX_PASSWORD];
    char inputPassword[MAX_PASSWORD];

    printf("Enter your email: ");
    scanf("%s", oldEmail);

    if (strcmp(oldEmail, currentEmail) != 0) {
        printf("Incorrect email. Please try again.\n");
        return 1;
    }

    printf("Enter your password: ");
    scanf("%s", inputPassword);

    if (strcmp(inputPassword, currentPassword) != 0) {
        printf("Incorrect password. Please try again.\n");
        return 1;
    }

    printf("Enter new email: ");
    scanf("%s", newEmail);

    if (strcmp(newEmail, oldEmail) == 0) {
        printf("New email must be different from the old email.\n");
        return 1;
    }

    printf("Confirm your password to change email: ");
    scanf("%s", confirmPassword);

    if (strcmp(confirmPassword, currentPassword) != 0) {
        printf("Password confirmation failed. Please try again.\n");
        return 1;
    }

    strcpy(currentEmail, newEmail);
    printf("Email updated successfully to %s\n", currentEmail);

    return 0;
}