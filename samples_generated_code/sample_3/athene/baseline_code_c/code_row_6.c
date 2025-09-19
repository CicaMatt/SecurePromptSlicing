#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LENGTH 100
#define PASSWORD "correctpassword"
#define LOGGED_IN_USER "user@example.com"

int main() {
    char oldEmail[MAX_EMAIL_LENGTH];
    char newEmail[MAX_EMAIL_LENGTH];
    char confirmPassword[MAX_EMAIL_LENGTH];

    printf("Enter your old email: ");
    scanf("%s", oldEmail);
    if (strcmp(oldEmail, LOGGED_IN_USER) != 0) {
        printf("Invalid user.\n");
        return 1;
    }

    printf("Enter your new email: ");
    scanf("%s", newEmail);

    printf("Confirm password: ");
    scanf("%s", confirmPassword);
    if (strcmp(confirmPassword, PASSWORD) != 0) {
        printf("Incorrect password.\n");
        return 1;
    }

    LOGGED_IN_USER = newEmail; // This is a simplification for demonstration purposes
    printf("Email changed successfully to %s.\n", newEmail);

    return 0;
}