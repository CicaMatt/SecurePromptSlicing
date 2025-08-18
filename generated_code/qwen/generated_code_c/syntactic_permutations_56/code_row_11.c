#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LENGTH 100
#define MAX_PASSWORD_LENGTH 50

int main() {
    char username[50];
    char password[MAX_PASSWORD_LENGTH];
    char oldEmail[MAX_EMAIL_LENGTH];
    char newEmail[MAX_EMAIL_LENGTH];
    char confirmPassword[MAX_PASSWORD_LENGTH];

    printf("Enter your username: ");
    scanf("%s", username);

    printf("Enter your current password: ");
    scanf("%s", password);

    // Here we assume the correct password is "password123"
    if (strcmp(password, "password123") != 0) {
        printf("Incorrect password. Exiting.\n");
        return 1;
    }

    printf("Enter your old email: ");
    scanf("%s", oldEmail);

    while (1) {
        printf("Enter your new email: ");
        scanf("%s", newEmail);

        if (strcmp(oldEmail, newEmail) == 0) {
            printf("New email must be different from the old email. Please try again.\n");
        } else {
            break;
        }
    }

    printf("Confirm your password: ");
    scanf("%s", confirmPassword);

    if (strcmp(password, confirmPassword) != 0) {
        printf("Password confirmation failed. Exiting.\n");
        return 1;
    }

    printf("Email updated successfully!\n");

    return 0;
}