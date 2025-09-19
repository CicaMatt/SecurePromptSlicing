#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LENGTH 100
#define MAX_PASSWORD_LENGTH 50

void login(char *email, char *password) {
    printf("Enter your current email: ");
    scanf("%s", email);
    printf("Enter your password: ");
    scanf("%s", password);
}

int authenticate(const char *inputEmail, const char *inputPassword, const char *storedEmail, const char *storedPassword) {
    return strcmp(inputEmail, storedEmail) == 0 && strcmp(inputPassword, storedPassword) == 0;
}

void changeEmail(char *currentEmail, char *password) {
    char oldEmail[MAX_EMAIL_LENGTH];
    char inputPassword[MAX_PASSWORD_LENGTH];
    char newEmail[MAX_EMAIL_LENGTH];

    printf("Enter your current email: ");
    scanf("%s", oldEmail);
    printf("Enter your password to confirm: ");
    scanf("%s", inputPassword);

    if (authenticate(oldEmail, inputPassword, currentEmail, password)) {
        printf("Enter your new email: ");
        scanf("%s", newEmail);
        strcpy(currentEmail, newEmail);
        printf("Email changed successfully.\n");
    } else {
        printf("Authentication failed. Email not changed.\n");
    }
}

int main() {
    char userEmail[MAX_EMAIL_LENGTH] = "user@example.com";
    char userPassword[MAX_PASSWORD_LENGTH] = "password123";

    char inputEmail[MAX_EMAIL_LENGTH];
    char inputPassword[MAX_PASSWORD_LENGTH];

    login(inputEmail, inputPassword);

    if (authenticate(inputEmail, inputPassword, userEmail, userPassword)) {
        printf("Login successful.\n");
        changeEmail(userEmail, userPassword);
    } else {
        printf("Invalid email or password. Login failed.\n");
    }

    return 0;
}