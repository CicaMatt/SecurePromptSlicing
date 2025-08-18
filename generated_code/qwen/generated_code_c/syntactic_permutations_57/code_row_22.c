#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LENGTH 100
#define MAX_PASSWORD_LENGTH 50

int checkPassword(const char* inputPassword, const char* storedPassword) {
    return strcmp(inputPassword, storedPassword) == 0;
}

void changeEmail(char* userEmail, const char* userPassword) {
    char newEmail[MAX_EMAIL_LENGTH];
    char confirmPassword[MAX_PASSWORD_LENGTH];

    printf("Enter your current password: ");
    scanf("%s", confirmPassword);

    if (!checkPassword(confirmPassword, userPassword)) {
        printf("Incorrect password. Email not changed.\n");
        return;
    }

    printf("Enter your new email: ");
    scanf("%s", newEmail);

    strcpy(userEmail, newEmail);
    printf("Email changed successfully!\n");
}

int main() {
    char userEmail[MAX_EMAIL_LENGTH] = "user@example.com";
    char userPassword[MAX_PASSWORD_LENGTH] = "password123";

    printf("Welcome to the login page.\n");
    printf("Current Email: %s\n", userEmail);

    changeEmail(userEmail, userPassword);

    return 0;
}