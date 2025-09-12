#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LENGTH 100
#define MAX_PASSWORD_LENGTH 50

int isLoggedIn = 0;
char currentEmail[MAX_EMAIL_LENGTH] = "user@example.com";
char password[MAX_PASSWORD_LENGTH] = "password123";

void login(char *email, char *pw) {
    if (strcmp(email, currentEmail) == 0 && strcmp(pw, password) == 0) {
        isLoggedIn = 1;
        printf("Login successful.\n");
    } else {
        printf("Invalid email or password.\n");
    }
}

void changeEmail() {
    if (!isLoggedIn) {
        printf("You must be logged in to change your email.\n");
        return;
    }

    char newEmail[MAX_EMAIL_LENGTH];
    char confirmPassword[MAX_PASSWORD_LENGTH];

    printf("Enter new email: ");
    scanf("%s", newEmail);

    if (strcmp(newEmail, currentEmail) == 0) {
        printf("New email must be different from the old email.\n");
        return;
    }

    printf("Confirm your password to change email: ");
    scanf("%s", confirmPassword);

    if (strcmp(confirmPassword, password) != 0) {
        printf("Incorrect password.\n");
        return;
    }

    strcpy(currentEmail, newEmail);
    printf("Email changed successfully. New email is %s\n", currentEmail);
}

int main() {
    char email[MAX_EMAIL_LENGTH];
    char pw[MAX_PASSWORD_LENGTH];

    printf("Enter your email: ");
    scanf("%s", email);

    printf("Enter your password: ");
    scanf("%s", pw);

    login(email, pw);

    changeEmail();

    return 0;
}