#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LENGTH 50
#define MAX_PASSWORD_LENGTH 20

typedef struct {
    char email[MAX_EMAIL_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
    int isLoggedIn;
} User;

void login(User *user, const char *email, const char *password) {
    if (strcmp(user->email, email) == 0 && strcmp(user->password, password) == 0) {
        user->isLoggedIn = 1;
        printf("Login successful.\n");
    } else {
        printf("Login failed. Incorrect email or password.\n");
    }
}

void changeEmail(User *user, const char *oldEmail, const char *confirmPassword, const char *newEmail) {
    if (!user->isLoggedIn) {
        printf("You must be logged in to change your email.\n");
        return;
    }

    if (strcmp(user->email, oldEmail) == 0 && strcmp(user->password, confirmPassword) == 0) {
        strcpy(user->email, newEmail);
        printf("Email changed successfully.\n");
    } else {
        printf("Incorrect old email or password. Email not changed.\n");
    }
}

int main() {
    User user = {"user@example.com", "securepassword", 0};
    char email[MAX_EMAIL_LENGTH], password[MAX_PASSWORD_LENGTH];
    char oldEmail[MAX_EMAIL_LENGTH], confirmPassword[MAX_PASSWORD_LENGTH], newEmail[MAX_EMAIL_LENGTH];

    printf("Enter your email to login: ");
    scanf("%49s", email);
    printf("Enter your password to login: ");
    scanf("%19s", password);

    login(&user, email, password);

    if (user.isLoggedIn) {
        printf("Enter your old email: ");
        scanf("%49s", oldEmail);
        printf("Confirm your password: ");
        scanf("%19s", confirmPassword);
        printf("Enter your new email: ");
        scanf("%49s", newEmail);

        changeEmail(&user, oldEmail, confirmPassword, newEmail);
    }

    return 0;
}