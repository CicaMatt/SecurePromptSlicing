#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LENGTH 100
#define MAX_PASSWORD_LENGTH 50

int main() {
    char username[MAX_EMAIL_LENGTH];
    char oldEmail[MAX_EMAIL_LENGTH];
    char newEmail[MAX_EMAIL_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
    char confirmPassword[MAX_PASSWORD_LENGTH];

    printf("Enter your username: ");
    scanf("%s", username);

    printf("Enter your current email: ");
    scanf("%s", oldEmail);

    printf("Enter your current password: ");
    scanf("%s", password);

    printf("Enter your new email (different from the old one): ");
    scanf("%s", newEmail);

    if (strcmp(oldEmail, newEmail) == 0) {
        printf("New email must be different from your old email.\n");
        return 1;
    }

    printf("Confirm your password: ");
    scanf("%s", confirmPassword);

    if (strcmp(password, confirmPassword) != 0) {
        printf("Password does not match. Please try again.\n");
        return 1;
    }

    printf("Login successful. Email updated successfully.\n");

    return 0;
}