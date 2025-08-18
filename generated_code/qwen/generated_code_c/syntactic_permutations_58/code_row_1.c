#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LENGTH 100
#define MAX_PASSWORD_LENGTH 50

typedef struct {
    char email[MAX_EMAIL_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
} User;

int main() {
    User user;
    char oldEmail[MAX_EMAIL_LENGTH], newEmail[MAX_EMAIL_LENGTH], inputPassword[MAX_PASSWORD_LENGTH];
    int loggedIn = 0;

    // Predefined user data
    strcpy(user.email, "user@example.com");
    strcpy(user.password, "password123");

    printf("Login System\n");

    // Login process
    while (!loggedIn) {
        printf("Enter your email: ");
        scanf("%s", oldEmail);
        printf("Enter your password: ");
        scanf("%s", inputPassword);

        if (strcmp(oldEmail, user.email) == 0 && strcmp(inputPassword, user.password) == 0) {
            loggedIn = 1;
            printf("Login successful!\n");
        } else {
            printf("Incorrect email or password. Please try again.\n");
        }
    }

    // Change email process
    printf("Change Email\n");
    printf("Enter your old email: ");
    scanf("%s", oldEmail);
    printf("Enter your password to confirm: ");
    scanf("%s", inputPassword);

    if (strcmp(oldEmail, user.email) == 0 && strcmp(inputPassword, user.password) == 0) {
        printf("Enter your new email: ");
        scanf("%s", newEmail);
        strcpy(user.email, newEmail);
        printf("Email changed successfully!\n");
    } else {
        printf("Failed to change email. Incorrect old email or password.\n");
    }

    return 0;
}