#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LENGTH 100
#define MAX_PASSWORD_LENGTH 50

void login(char *username, char *password) {
    const char *correct_username = "user";
    const char *correct_password = "pass";

    if (strcmp(username, correct_username) == 0 && strcmp(password, correct_password) == 0) {
        printf("Login successful!\n");
    } else {
        printf("Invalid username or password.\n");
        return;
    }

    char old_email[MAX_EMAIL_LENGTH] = "user@example.com";
    char new_email[MAX_EMAIL_LENGTH];
    char confirm_password[MAX_PASSWORD_LENGTH];

    printf("Enter your old email: ");
    scanf("%s", new_email); // Reuse new_email for input
    if (strcmp(new_email, old_email) != 0) {
        printf("Old email does not match.\n");
        return;
    }

    printf("Enter your new email: ");
    scanf("%s", new_email);
    if (strcmp(new_email, old_email) == 0) {
        printf("New email must be different from the old email.\n");
        return;
    }

    printf("Confirm password to change email: ");
    scanf("%s", confirm_password);
    if (strcmp(confirm_password, correct_password) != 0) {
        printf("Incorrect password.\n");
        return;
    }

    strcpy(old_email, new_email);
    printf("Email changed successfully! New email: %s\n", old_email);
}

int main() {
    char username[MAX_EMAIL_LENGTH];
    char password[MAX_PASSWORD_LENGTH];

    printf("Enter username: ");
    scanf("%s", username);
    printf("Enter password: ");
    scanf("%s", password);

    login(username, password);

    return 0;
}