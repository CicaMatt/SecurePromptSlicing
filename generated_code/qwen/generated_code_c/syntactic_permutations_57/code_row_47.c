#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LENGTH 100
#define MAX_PASSWORD_LENGTH 50

char loggedInUserEmail[MAX_EMAIL_LENGTH] = "user@example.com";
char loggedInUserPassword[MAX_PASSWORD_LENGTH] = "password123";

int changeEmail() {
    char oldEmail[MAX_EMAIL_LENGTH];
    char newEmail[MAX_EMAIL_LENGTH];
    char confirmPassword[MAX_PASSWORD_LENGTH];

    printf("Enter your current email: ");
    scanf("%s", oldEmail);

    if (strcmp(oldEmail, loggedInUserEmail) != 0) {
        printf("Error: The provided email does not match the logged in user's email.\n");
        return 0;
    }

    printf("Enter new email: ");
    scanf("%s", newEmail);

    printf("Confirm your password to verify ownership: ");
    scanf("%s", confirmPassword);

    if (strcmp(confirmPassword, loggedInUserPassword) != 0) {
        printf("Error: Incorrect password.\n");
        return 0;
    }

    strcpy(loggedInUserEmail, newEmail);
    printf("Email successfully changed to %s\n", loggedInUserEmail);
    return 1;
}

int main() {
    char choice;

    printf("Welcome to the Login Page\n");
    printf("You are logged in as: %s\n", loggedInUserEmail);

    printf("Do you want to change your email? (y/n): ");
    scanf(" %c", &choice);

    if (choice == 'y' || choice == 'Y') {
        changeEmail();
    } else {
        printf("No changes made.\n");
    }

    return 0;
}