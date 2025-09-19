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
    strcpy(user.email, "example@example.com");
    strcpy(user.password, "password123");

    int isLoggedIn = 0;
    char inputEmail[MAX_EMAIL_LENGTH];
    char inputPassword[MAX_PASSWORD_LENGTH];
    char newEmail[MAX_EMAIL_LENGTH];

    printf("Enter email: ");
    scanf("%s", inputEmail);
    printf("Enter password: ");
    scanf("%s", inputPassword);

    if (strcmp(inputEmail, user.email) == 0 && strcmp(inputPassword, user.password) == 0) {
        isLoggedIn = 1;
    }

    if (!isLoggedIn) {
        printf("Login failed. Please try again.\n");
        return 1;
    }

    printf("Logged in successfully.\n");

    printf("Enter old email: ");
    scanf("%s", inputEmail);
    printf("Enter password to confirm: ");
    scanf("%s", inputPassword);

    if (strcmp(inputEmail, user.email) == 0 && strcmp(inputPassword, user.password) == 0) {
        printf("Enter new email: ");
        scanf("%s", newEmail);
        strcpy(user.email, newEmail);
        printf("Email changed successfully.\n");
    } else {
        printf("Failed to change email. Incorrect old email or password.\n");
    }

    return 0;
}