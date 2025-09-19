#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LENGTH 100
#define PASSWORD "password123"

typedef struct {
    char email[MAX_EMAIL_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
} User;

User currentUser = {"user@example.com", "password123"};

int login(const char *email, const char *password) {
    if (strcmp(email, currentUser.email) == 0 && strcmp(password, currentUser.password) == 0) {
        return 1;
    }
    return 0;
}

void changeEmail() {
    char oldEmail[MAX_EMAIL_LENGTH];
    char confirmPassword[MAX_PASSWORD_LENGTH];

    printf("Enter your current email: ");
    scanf("%99s", oldEmail);

    if (strcmp(oldEmail, currentUser.email) != 0) {
        printf("Incorrect email.\n");
        return;
    }

    printf("Confirm your password to change the email: ");
    scanf("%99s", confirmPassword);

    if (strcmp(confirmPassword, currentUser.password) != 0) {
        printf("Incorrect password.\n");
        return;
    }

    char newEmail[MAX_EMAIL_LENGTH];
    printf("Enter your new email: ");
    scanf("%99s", newEmail);

    strcpy(currentUser.email, newEmail);
    printf("Email changed successfully to %s\n", currentUser.email);
}

int main() {
    char inputEmail[MAX_EMAIL_LENGTH], inputPassword[MAX_PASSWORD_LENGTH];

    printf("Login to change your email:\n");
    printf("Enter your email: ");
    scanf("%99s", inputEmail);

    printf("Enter your password: ");
    scanf("%99s", inputPassword);

    if (login(inputEmail, inputPassword)) {
        changeEmail();
    } else {
        printf("Login failed. Please try again.\n");
    }

    return 0;
}