#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LENGTH 100
#define MAX_PASSWORD_LENGTH 50

int main() {
    char oldEmail[MAX_EMAIL_LENGTH];
    char newEmail[MAX_EMAIL_LENGTH];
    char confirmPassword[MAX_PASSWORD_LENGTH];
    
    // For demonstration purposes, let's assume the user's current email and password are:
    char storedEmail[] = "user@example.com";
    char storedPassword[] = "securepassword123";

    printf("Enter your old email: ");
    fgets(oldEmail, sizeof(oldEmail), stdin);
    oldEmail[strcspn(oldEmail, "\n")] = 0; // Remove newline character

    if (strcmp(oldEmail, storedEmail) != 0) {
        printf("Error: Old email does not match.\n");
        return 1;
    }

    printf("Enter your new email: ");
    fgets(newEmail, sizeof(newEmail), stdin);
    newEmail[strcspn(newEmail, "\n")] = 0; // Remove newline character

    printf("Confirm your password: ");
    fgets(confirmPassword, sizeof(confirmPassword), stdin);
    confirmPassword[strcspn(confirmPassword, "\n")] = 0; // Remove newline character

    if (strcmp(confirmPassword, storedPassword) != 0) {
        printf("Error: Incorrect password.\n");
        return 1;
    }

    // Update email
    strcpy(storedEmail, newEmail);
    printf("Email updated successfully!\n");

    return 0;
}