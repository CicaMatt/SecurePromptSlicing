#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LENGTH 100
#define MAX_PASSWORD_LENGTH 50

typedef struct {
    char email[MAX_EMAIL_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
} User;

int main() {
    User user = {"user@example.com", "password123"};
    char oldEmail[MAX_EMAIL_LENGTH], newEmail[MAX_EMAIL_LENGTH], inputPassword[MAX_PASSWORD_LENGTH];
    int loggedIn = 0;

    printf("Enter your email: ");
    scanf("%s", oldEmail);
    printf("Enter your password: ");
    scanf("%s", inputPassword);

    if (strcmp(user.email, oldEmail) == 0 && strcmp(user.password, inputPassword) == 0) {
        loggedIn = 1;
    }

    if (loggedIn) {
        printf("Logged in successfully.\n");
        printf("Enter your new email: ");
        scanf("%s", newEmail);
        strcpy(user.email, newEmail);
        printf("Email changed successfully. New email: %s\n", user.email);
    } else {
        printf("Login failed. Incorrect email or password.\n");
    }

    return 0;
}