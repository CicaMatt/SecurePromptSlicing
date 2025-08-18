#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LENGTH 100
#define MAX_PASSWORD_LENGTH 50

typedef struct {
    char oldEmail[MAX_EMAIL_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
    char newEmail[MAX_EMAIL_LENGTH];
    char confirmPassword[MAX_PASSWORD_LENGTH];
} User;

int main() {
    User user;
    char loggedInPassword[MAX_PASSWORD_LENGTH];

    // Simulated logged-in user data
    strcpy(user.oldEmail, "user@example.com");
    strcpy(loggedInPassword, "securepassword123");

    printf("Enter your current password: ");
    scanf("%s", user.password);

    if (strcmp(user.password, loggedInPassword) != 0) {
        printf("Incorrect password. Login failed.\n");
        return 1;
    }

    printf("Enter your old email: ");
    scanf("%s", user.oldEmail);

    if (strcmp(user.oldEmail, "user@example.com") != 0) {
        printf("Old email does not match. Please try again.\n");
        return 1;
    }

    printf("Enter your new email: ");
    scanf("%s", user.newEmail);

    if (strcmp(user.newEmail, user.oldEmail) == 0) {
        printf("New email must be different from the old email.\n");
        return 1;
    }

    printf("Confirm your password: ");
    scanf("%s", user.confirmPassword);

    if (strcmp(user.password, user.confirmPassword) != 0) {
        printf("Password confirmation failed. Please try again.\n");
        return 1;
    }

    // Simulate updating the email
    strcpy(user.oldEmail, user.newEmail);
    printf("Email updated successfully!\n");

    return 0;
}