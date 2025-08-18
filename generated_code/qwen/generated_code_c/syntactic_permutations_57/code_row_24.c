#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LENGTH 100
#define MAX_PASSWORD_LENGTH 50

int main() {
    char currentEmail[MAX_EMAIL_LENGTH] = "user@example.com";
    char currentPassword[MAX_PASSWORD_LENGTH] = "password123";
    char newEmail[MAX_EMAIL_LENGTH];
    char confirmPassword[MAX_PASSWORD_LENGTH];

    printf("Enter your current email: ");
    fgets(currentEmail, sizeof(currentEmail), stdin);
    currentEmail[strcspn(currentEmail, "\n")] = 0;

    printf("Enter your password to confirm: ");
    fgets(confirmPassword, sizeof(confirmPassword), stdin);
    confirmPassword[strcspn(confirmPassword, "\n")] = 0;

    if (strcmp(confirmPassword, currentPassword) != 0) {
        printf("Incorrect password. Please try again.\n");
        return 1;
    }

    printf("Enter your new email: ");
    fgets(newEmail, sizeof(newEmail), stdin);
    newEmail[strcspn(newEmail, "\n")] = 0;

    if (strlen(newEmail) == 0 || strlen(currentEmail) == 0) {
        printf("Invalid email address.\n");
        return 1;
    }

    printf("Your email has been changed from %s to %s\n", currentEmail, newEmail);

    return 0;
}