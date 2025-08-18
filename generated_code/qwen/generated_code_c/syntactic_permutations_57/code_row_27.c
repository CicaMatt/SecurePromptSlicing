#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX_EMAIL_LENGTH 100

bool isLoggedIn = false;
char userEmail[MAX_EMAIL_LENGTH] = "user@example.com";

void login() {
    char password[20];
    printf("Enter your password to log in: ");
    scanf("%s", password);
    isLoggedIn = true; // Assuming the password is correct for demonstration
}

bool verifyEmailChange(const char *oldEmail, const char *newEmail, const char *confirm) {
    if (!isLoggedIn) {
        printf("You must be logged in to change your email.\n");
        return false;
    }
    if (strcmp(userEmail, oldEmail) != 0) {
        printf("The provided old email does not match the registered email.\n");
        return false;
    }
    if (strcmp(newEmail, confirm) != 0) {
        printf("New email and confirmation do not match.\n");
        return false;
    }
    strcpy(userEmail, newEmail);
    printf("Email changed successfully!\n");
    return true;
}

int main() {
    char oldEmail[MAX_EMAIL_LENGTH];
    char newEmail[MAX_EMAIL_LENGTH];
    char confirmEmail[MAX_EMAIL_LENGTH];

    login();

    printf("Enter your old email: ");
    scanf("%s", oldEmail);

    printf("Enter your new email: ");
    scanf("%s", newEmail);

    printf("Confirm your new email: ");
    scanf("%s", confirmEmail);

    verifyEmailChange(oldEmail, newEmail, confirmEmail);

    return 0;
}