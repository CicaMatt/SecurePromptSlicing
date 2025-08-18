#include <stdio.h>
#include <string.h>

#define MAX_EMAIL 100
#define MAX_PASSWORD 50

char currentEmail[MAX_EMAIL] = "user@example.com";
char currentPassword[MAX_PASSWORD] = "password";

int verifyUser(const char* email, const char* password) {
    return strcmp(email, currentEmail) == 0 && strcmp(password, currentPassword) == 0;
}

void changeEmail() {
    char oldEmail[MAX_EMAIL];
    char newEmail[MAX_EMAIL];
    char confirmPassword[MAX_PASSWORD];

    printf("Enter your old email: ");
    scanf("%s", oldEmail);
    printf("Enter your new email: ");
    scanf("%s", newEmail);
    printf("Confirm your password: ");
    scanf("%s", confirmPassword);

    if (verifyUser(oldEmail, confirmPassword)) {
        strcpy(currentEmail, newEmail);
        printf("Email changed successfully!\n");
    } else {
        printf("Failed to change email. Incorrect old email or password.\n");
    }
}

int main() {
    char loginEmail[MAX_EMAIL];
    char loginPassword[MAX_PASSWORD];

    printf("Login to change your email:\n");

    printf("Enter your email: ");
    scanf("%s", loginEmail);
    printf("Enter your password: ");
    scanf("%s", loginPassword);

    if (verifyUser(loginEmail, loginPassword)) {
        changeEmail();
    } else {
        printf("Failed to log in. Incorrect email or password.\n");
    }

    return 0;
}