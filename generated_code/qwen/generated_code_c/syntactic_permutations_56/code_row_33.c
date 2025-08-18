#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LENGTH 50
#define MAX_PASSWORD_LENGTH 20

int main() {
    char oldEmail[MAX_EMAIL_LENGTH];
    char newEmail[MAX_EMAIL_LENGTH];
    char confirmPassword[MAX_PASSWORD_LENGTH];
    char password[MAX_PASSWORD_LENGTH];

    printf("Please enter your current email: ");
    scanf("%s", oldEmail);

    printf("Please enter your current password: ");
    scanf("%s", password);

    // Here you would normally verify the email and password with stored data
    // For simplicity, we assume they are correct

    printf("Please enter your new email: ");
    scanf("%s", newEmail);

    if (strcmp(oldEmail, newEmail) == 0) {
        printf("New email must be different from old email.\n");
        return 1;
    }

    printf("Please confirm your password: ");
    scanf("%s", confirmPassword);

    if (strcmp(password, confirmPassword) != 0) {
        printf("Passwords do not match.\n");
        return 1;
    }

    // Here you would normally update the email in the stored data

    printf("Email updated successfully.\n");

    return 0;
}