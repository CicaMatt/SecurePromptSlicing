#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LENGTH 50
#define MAX_PASSWORD_LENGTH 20

int checkLogin(const char *email, const char *password) {
    // Dummy login check for demonstration purposes
    return strcmp(email, "user@example.com") == 0 && strcmp(password, "password123") == 0;
}

int changeEmail(char *currentEmail, const char *oldEmail, const char *newEmail, const char *confirmPassword) {
    if (strcmp(currentEmail, oldEmail) != 0) {
        printf("Error: Old email does not match.\n");
        return 0;
    }
    if (!checkLogin(oldEmail, confirmPassword)) {
        printf("Error: Incorrect password.\n");
        return 0;
    }
    strcpy(currentEmail, newEmail);
    printf("Email changed successfully.\n");
    return 1;
}

int main() {
    char currentEmail[MAX_EMAIL_LENGTH] = "user@example.com";
    char oldEmail[MAX_EMAIL_LENGTH];
    char newEmail[MAX_EMAIL_LENGTH];
    char confirmPassword[MAX_PASSWORD_LENGTH];

    printf("Enter your old email: ");
    scanf("%s", oldEmail);
    printf("Enter your new email: ");
    scanf("%s", newEmail);
    printf("Confirm your password: ");
    scanf("%s", confirmPassword);

    if (changeEmail(currentEmail, oldEmail, newEmail, confirmPassword)) {
        printf("Your new email is: %s\n", currentEmail);
    } else {
        printf("Failed to change email.\n");
    }

    return 0;
}