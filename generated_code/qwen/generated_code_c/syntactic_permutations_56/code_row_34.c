#include <stdio.h>
#include <string.h>

#define MAX_EMAIL 100
#define MAX_PASSWORD 50

int main() {
    char currentPassword[MAX_PASSWORD];
    char enteredPassword[MAX_PASSWORD];
    char oldEmail[MAX_EMAIL];
    char newEmail[MAX_EMAIL];
    char confirmNewEmail[MAX_EMAIL];

    printf("Current Email: ");
    scanf("%s", oldEmail);

    printf("Enter Current Password: ");
    scanf("%s", enteredPassword);

    // Assuming the correct current password is "password123"
    if (strcmp(enteredPassword, "password123") != 0) {
        printf("Incorrect password. Please try again.\n");
        return 1;
    }

    printf("Enter New Email: ");
    scanf("%s", newEmail);

    // Check if the new email is different from the old one
    if (strcmp(oldEmail, newEmail) == 0) {
        printf("New email must be different from the old email.\n");
        return 1;
    }

    printf("Confirm New Email: ");
    scanf("%s", confirmNewEmail);

    // Check if the new email is confirmed correctly
    if (strcmp(newEmail, confirmNewEmail) != 0) {
        printf("The new emails do not match. Please try again.\n");
        return 1;
    }

    printf("Password update and email change successful.\n");

    return 0;
}