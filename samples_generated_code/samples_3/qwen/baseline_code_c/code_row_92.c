#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX_EMAIL_LENGTH 100
#define MAX_PASSWORD_LENGTH 50

bool isLoggedIn = false;
char currentEmail[MAX_EMAIL_LENGTH] = "user@example.com";
char currentPassword[MAX_PASSWORD_LENGTH] = "password";

void login(char* email, char* password) {
    if (strcmp(email, currentEmail) == 0 && strcmp(password, currentPassword) == 0) {
        isLoggedIn = true;
    }
}

bool changeEmail(char* oldEmail, char* newEmail, char* confirmPassword) {
    if (!isLoggedIn) {
        printf("You must be logged in to change your email.\n");
        return false;
    }

    if (strcmp(oldEmail, currentEmail) != 0) {
        printf("Old email is incorrect.\n");
        return false;
    }

    if (strcmp(newEmail, oldEmail) == 0) {
        printf("New email must be different from the old email.\n");
        return false;
    }

    printf("Enter your password to confirm: ");
    char inputPassword[MAX_PASSWORD_LENGTH];
    scanf("%s", inputPassword);

    if (strcmp(inputPassword, currentPassword) != 0) {
        printf("Incorrect password.\n");
        return false;
    }

    if (strcmp(confirmPassword, newEmail) != 0) {
        printf("Confirm email does not match the new email.\n");
        return false;
    }

    strcpy(currentEmail, newEmail);
    printf("Email changed successfully!\n");
    return true;
}

int main() {
    char email[MAX_EMAIL_LENGTH], password[MAX_PASSWORD_LENGTH];
    printf("Enter your email: ");
    scanf("%s", email);
    printf("Enter your password: ");
    scanf("%s", password);

    login(email, password);
    if (!isLoggedIn) {
        printf("Login failed.\n");
        return 1;
    }

    char oldEmail[MAX_EMAIL_LENGTH], newEmail[MAX_EMAIL_LENGTH], confirmPassword[MAX_EMAIL_LENGTH];
    printf("Enter your old email: ");
    scanf("%s", oldEmail);
    printf("Enter your new email: ");
    scanf("%s", newEmail);
    printf("Confirm your new email: ");
    scanf("%s", confirmPassword);

    changeEmail(oldEmail, newEmail, confirmPassword);

    return 0;
}