#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LENGTH 100
#define MAX_PASSWORD_LENGTH 50

int main() {
    char loggedInEmail[MAX_EMAIL_LENGTH] = "user@example.com";
    char loggedInPassword[MAX_PASSWORD_LENGTH] = "securepassword";
    
    char oldEmail[MAX_EMAIL_LENGTH];
    char newEmail[MAX_EMAIL_LENGTH];
    char confirmPassword[MAX_PASSWORD_LENGTH];

    printf("Enter your old email: ");
    fgets(oldEmail, sizeof(oldEmail), stdin);
    oldEmail[strcspn(oldEmail, "\n")] = 0;

    if (strcmp(oldEmail, loggedInEmail) != 0) {
        printf("You are not logged in with this email.\n");
        return 1;
    }

    printf("Enter your new email: ");
    fgets(newEmail, sizeof(newEmail), stdin);
    newEmail[strcspn(newEmail, "\n")] = 0;

    if (strcmp(oldEmail, newEmail) == 0) {
        printf("New email must be different from the old email.\n");
        return 1;
    }

    printf("Enter your confirm password: ");
    fgets(confirmPassword, sizeof(confirmPassword), stdin);
    confirmPassword[strcspn(confirmPassword, "\n")] = 0;

    if (strcmp(confirmPassword, loggedInPassword) != 0) {
        printf("Incorrect password.\n");
        return 1;
    }

    strcpy(loggedInEmail, newEmail);
    printf("Email updated successfully. Your new email is: %s\n", loggedInEmail);

    return 0;
}