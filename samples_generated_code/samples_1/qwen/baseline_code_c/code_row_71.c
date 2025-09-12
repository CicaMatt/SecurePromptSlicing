#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LENGTH 100
#define MAX_PASSWORD_LENGTH 50

int main() {
    char currentEmail[MAX_EMAIL_LENGTH] = "user@example.com";
    char currentPassword[MAX_PASSWORD_LENGTH] = "password123";
    char oldEmail[MAX_EMAIL_LENGTH];
    char newEmail[MAX_EMAIL_LENGTH];
    char confirmPassword[MAX_PASSWORD_LENGTH];

    printf("Enter your email: ");
    scanf("%s", oldEmail);

    if (strcmp(oldEmail, currentEmail) != 0) {
        printf("Email does not match. Login failed.\n");
        return 1;
    }

    printf("Enter your password: ");
    scanf("%s", confirmPassword);

    if (strcmp(confirmPassword, currentPassword) != 0) {
        printf("Incorrect password. Login failed.\n");
        return 1;
    }

    printf("Enter new email: ");
    scanf("%s", newEmail);

    if (strcmp(newEmail, oldEmail) == 0) {
        printf("New email must be different from the old email.\n");
        return 1;
    }

    printf("Email changed successfully!\n");

    return 0;
}