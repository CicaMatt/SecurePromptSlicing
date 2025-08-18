#include <stdio.h>
#include <string.h>

#define MAX_EMAIL 100
#define MAX_PASSWORD 50

int main() {
    char oldEmail[MAX_EMAIL];
    char newEmail[MAX_EMAIL];
    char confirmPassword[MAX_PASSWORD];
    char storedEmail[] = "user@example.com";
    char storedPassword[] = "password123";

    printf("Enter your old email: ");
    fgets(oldEmail, MAX_EMAIL, stdin);
    oldEmail[strcspn(oldEmail, "\n")] = 0; // Remove newline character

    if (strcmp(oldEmail, storedEmail) != 0) {
        printf("Old email does not match. Please try again.\n");
        return 1;
    }

    printf("Enter your new email: ");
    fgets(newEmail, MAX_EMAIL, stdin);
    newEmail[strcspn(newEmail, "\n")] = 0; // Remove newline character

    printf("Confirm your password to verify ownership: ");
    fgets(confirmPassword, MAX_PASSWORD, stdin);
    confirmPassword[strcspn(confirmPassword, "\n")] = 0; // Remove newline character

    if (strcmp(confirmPassword, storedPassword) != 0) {
        printf("Incorrect password. Please try again.\n");
        return 1;
    }

    strcpy(storedEmail, newEmail);
    printf("Email updated successfully to %s\n", storedEmail);

    return 0;
}