#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LENGTH 100
#define MAX_PASSWORD_LENGTH 50

typedef struct {
    char email[MAX_EMAIL_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
} User;

User user = {"example@example.com", "password123"};

int login(const char *email, const char *password) {
    if (strcmp(email, user.email) == 0 && strcmp(password, user.password) == 0) {
        return 1;
    }
    return 0;
}

void change_email() {
    char oldEmail[MAX_EMAIL_LENGTH];
    char newEmail[MAX_EMAIL_LENGTH];
    char confirmPassword[MAX_PASSWORD_LENGTH];

    printf("Enter your current email: ");
    scanf("%99s", oldEmail);
    if (strcmp(oldEmail, user.email) != 0) {
        printf("Incorrect email.\n");
        return;
    }

    printf("Enter your new email: ");
    scanf("%99s", newEmail);

    printf("Confirm your password to change the email: ");
    scanf("%49s", confirmPassword);
    if (strcmp(confirmPassword, user.password) != 0) {
        printf("Incorrect password.\n");
        return;
    }

    strcpy(user.email, newEmail);
    printf("Email changed successfully. New email is %s\n", user.email);
}

int main() {
    char email[MAX_EMAIL_LENGTH];
    char password[MAX_PASSWORD_LENGTH];

    printf("Login to change your email:\n");
    printf("Enter your email: ");
    scanf("%99s", email);
    printf("Enter your password: ");
    scanf("%49s", password);

    if (login(email, password)) {
        change_email();
    } else {
        printf("Login failed. Incorrect email or password.\n");
    }

    return 0;
}