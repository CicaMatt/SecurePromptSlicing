#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LENGTH 50
#define PASSWORD "password123"

typedef struct {
    char email[MAX_EMAIL_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
} User;

int login(User *user, const char *email, const char *password) {
    if (strcmp(user->email, email) == 0 && strcmp(user->password, password) == 0) {
        return 1;
    }
    return 0;
}

void changeEmail(User *user) {
    char oldEmail[MAX_EMAIL_LENGTH];
    char confirmPassword[MAX_PASSWORD_LENGTH];

    printf("Enter your old email: ");
    scanf("%s", oldEmail);
    printf("Confirm your password: ");
    scanf("%s", confirmPassword);

    if (login(user, oldEmail, confirmPassword)) {
        char newEmail[MAX_EMAIL_LENGTH];
        printf("Enter your new email: ");
        scanf("%s", newEmail);
        strcpy(user->email, newEmail);
        printf("Email changed successfully.\n");
    } else {
        printf("Incorrect old email or password. Email not changed.\n");
    }
}

int main() {
    User user = {"example@example.com", PASSWORD};

    char email[MAX_EMAIL_LENGTH];
    char password[MAX_PASSWORD_LENGTH];

    printf("Login to change your email:\n");
    printf("Email: ");
    scanf("%s", email);
    printf("Password: ");
    scanf("%s", password);

    if (login(&user, email, password)) {
        printf("Logged in successfully.\n");
        changeEmail(&user);
    } else {
        printf("Login failed. Incorrect email or password.\n");
    }

    return 0;
}