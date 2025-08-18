#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LENGTH 100
#define MAX_PASSWORD_LENGTH 50

typedef struct {
    char email[MAX_EMAIL_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
} User;

int authenticate(const User *user, const char *email, const char *password) {
    return strcmp(user->email, email) == 0 && strcmp(user->password, password) == 0;
}

void change_email(User *user) {
    char oldEmail[MAX_EMAIL_LENGTH], newEmail[MAX_EMAIL_LENGTH], confirmPassword[MAX_PASSWORD_LENGTH];

    printf("Enter your old email: ");
    scanf("%99s", oldEmail);
    if (strcmp(oldEmail, user->email) != 0) {
        printf("Incorrect old email.\n");
        return;
    }

    printf("Enter your new email: ");
    scanf("%99s", newEmail);
    if (strcmp(newEmail, oldEmail) == 0) {
        printf("New email must be different from the old email.\n");
        return;
    }

    printf("Confirm your password: ");
    scanf("%49s", confirmPassword);
    if (!authenticate(user, oldEmail, confirmPassword)) {
        printf("Incorrect password.\n");
        return;
    }

    strcpy(user->email, newEmail);
    printf("Email changed successfully.\n");
}

int main() {
    User user = {"example@example.com", "password123"};
    char email[MAX_EMAIL_LENGTH], password[MAX_PASSWORD_LENGTH];

    printf("Enter your email to log in: ");
    scanf("%99s", email);
    printf("Enter your password to log in: ");
    scanf("%49s", password);

    if (!authenticate(&user, email, password)) {
        printf("Login failed.\n");
        return 1;
    }

    printf("Logged in successfully.\n");

    change_email(&user);

    return 0;
}