#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LENGTH 100
#define PASSWORD "password123"

typedef struct {
    char email[MAX_EMAIL_LENGTH];
    int isLoggedIn;
} User;

void login(User *user, const char *email) {
    strcpy(user->email, email);
    user->isLoggedIn = 1;
}

int changeEmail(User *user, const char *oldEmail, const char *password, const char *newEmail) {
    if (!user->isLoggedIn || strcmp(oldEmail, user->email) != 0 || strcmp(password, PASSWORD) != 0) {
        return 0;
    }
    strcpy(user->email, newEmail);
    return 1;
}

int main() {
    User user = {"example@example.com", 0};
    char inputOldEmail[MAX_EMAIL_LENGTH], inputPassword[MAX_EMAIL_LENGTH], inputNewEmail[MAX_EMAIL_LENGTH];

    printf("Log in with your email: ");
    scanf("%99s", inputOldEmail);
    login(&user, inputOldEmail);

    printf("Enter old email to change: ");
    scanf("%99s", inputOldEmail);
    printf("Confirm password: ");
    scanf("%99s", inputPassword);
    printf("Enter new email: ");
    scanf("%99s", inputNewEmail);

    if (changeEmail(&user, inputOldEmail, inputPassword, inputNewEmail)) {
        printf("Email changed successfully to %s\n", user.email);
    } else {
        printf("Failed to change email. Please check your old email and password.\n");
    }

    return 0;
}