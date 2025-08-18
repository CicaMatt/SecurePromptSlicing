#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LEN 100
#define MAX_PASSWORD_LEN 50

int isLoggedIn = 0;
char currentEmail[MAX_EMAIL_LEN] = "user@example.com";
char password[MAX_PASSWORD_LEN] = "securepassword";

void login(const char *email, const char *pwd) {
    if (strcmp(email, currentEmail) == 0 && strcmp(pwd, password) == 0) {
        isLoggedIn = 1;
        printf("Login successful.\n");
    } else {
        printf("Login failed. Incorrect email or password.\n");
    }
}

void changeEmail() {
    char oldEmail[MAX_EMAIL_LEN];
    char newEmail[MAX_EMAIL_LEN];
    char confirmPassword[MAX_PASSWORD_LEN];

    if (!isLoggedIn) {
        printf("You must be logged in to change your email.\n");
        return;
    }

    printf("Enter your old email: ");
    scanf("%99s", oldEmail);
    if (strcmp(oldEmail, currentEmail) != 0) {
        printf("Incorrect old email.\n");
        return;
    }

    printf("Enter your new email: ");
    scanf("%99s", newEmail);
    if (strcmp(newEmail, currentEmail) == 0) {
        printf("New email must be different from the old email.\n");
        return;
    }

    printf("Confirm your password: ");
    scanf("%49s", confirmPassword);
    if (strcmp(confirmPassword, password) != 0) {
        printf("Incorrect password.\n");
        return;
    }

    strcpy(currentEmail, newEmail);
    printf("Email changed successfully. New email: %s\n", currentEmail);
}

int main() {
    char email[MAX_EMAIL_LEN];
    char pwd[MAX_PASSWORD_LEN];

    printf("Enter your email to log in: ");
    scanf("%99s", email);
    printf("Enter your password to log in: ");
    scanf("%49s", pwd);

    login(email, pwd);

    if (isLoggedIn) {
        changeEmail();
    }

    return 0;
}