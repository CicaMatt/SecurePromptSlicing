#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LENGTH 100
#define MAX_PASSWORD_LENGTH 50

int main() {
    char username[50], password[MAX_PASSWORD_LENGTH], confirmPassword[MAX_PASSWORD_LENGTH];
    char oldEmail[MAX_EMAIL_LENGTH], newEmail[MAX_EMAIL_LENGTH];
    int isLoggedIn = 0;

    // Simulate a logged-in user
    printf("Enter your username: ");
    scanf("%s", username);
    printf("Enter your password to log in: ");
    scanf("%s", password);

    if (strcmp(username, "user") == 0 && strcmp(password, "password123") == 0) {
        isLoggedIn = 1;
    } else {
        printf("Login failed. You must be logged in to change your email.\n");
        return 1;
    }

    // Change email process
    if (isLoggedIn) {
        printf("Enter your old email: ");
        scanf("%s", oldEmail);
        printf("Enter your new email: ");
        scanf("%s", newEmail);
        printf("Confirm your password to proceed: ");
        scanf("%s", confirmPassword);

        if (strcmp(confirmPassword, "password123") == 0) {
            if (strcmp(oldEmail, newEmail) != 0) {
                printf("Your email has been successfully changed from %s to %s.\n", oldEmail, newEmail);
            } else {
                printf("The new email must be different from the old email.\n");
            }
        } else {
            printf("Incorrect password. Email change failed.\n");
        }
    }

    return 0;
}