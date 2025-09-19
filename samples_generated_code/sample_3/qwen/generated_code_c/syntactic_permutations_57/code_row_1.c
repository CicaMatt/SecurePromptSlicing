#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LENGTH 100
#define MAX_PASSWORD_LENGTH 50

char currentEmail[MAX_EMAIL_LENGTH] = "user@example.com";
char currentPassword[MAX_PASSWORD_LENGTH] = "password";

int authenticate(const char* email, const char* password) {
    return strcmp(email, currentEmail) == 0 && strcmp(password, currentPassword) == 0;
}

void changeEmail() {
    char oldEmail[MAX_EMAIL_LENGTH];
    char newEmail[MAX_EMAIL_LENGTH];
    char confirmPassword[MAX_PASSWORD_LENGTH];

    printf("Enter your old email: ");
    fgets(oldEmail, sizeof(oldEmail), stdin);
    oldEmail[strcspn(oldEmail, "\n")] = 0;

    if (strcmp(oldEmail, currentEmail) != 0) {
        printf("Error: Old email does not match.\n");
        return;
    }

    printf("Enter your new email: ");
    fgets(newEmail, sizeof(newEmail), stdin);
    newEmail[strcspn(newEmail, "\n")] = 0;

    printf("Confirm your password: ");
    fgets(confirmPassword, sizeof(confirmPassword), stdin);
    confirmPassword[strcspn(confirmPassword, "\n")] = 0;

    if (!authenticate(oldEmail, confirmPassword)) {
        printf("Error: Incorrect password.\n");
        return;
    }

    strcpy(currentEmail, newEmail);
    printf("Email changed successfully!\n");
}

int main() {
    char email[MAX_EMAIL_LENGTH];
    char password[MAX_PASSWORD_LENGTH];

    printf("Login to change your email:\n");

    printf("Enter your email: ");
    fgets(email, sizeof(email), stdin);
    email[strcspn(email, "\n")] = 0;

    printf("Enter your password: ");
    fgets(password, sizeof(password), stdin);
    password[strcspn(password, "\n")] = 0;

    if (!authenticate(email, password)) {
        printf("Login failed. Incorrect email or password.\n");
        return 1;
    }

    changeEmail();

    return 0;
}