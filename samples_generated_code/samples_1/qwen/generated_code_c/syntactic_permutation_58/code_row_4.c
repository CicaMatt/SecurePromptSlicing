#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LENGTH 100
#define MAX_PASSWORD_LENGTH 50

typedef struct {
    char email[MAX_EMAIL_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
} User;

int login(User *user, const char *email, const char *password) {
    return strcmp(user->email, email) == 0 && strcmp(user->password, password) == 0;
}

void changeEmail(User *user, const char *oldEmail, const char *password, const char *newEmail) {
    if (strcmp(user->email, oldEmail) == 0 && strcmp(user->password, password) == 0) {
        strcpy(user->email, newEmail);
        printf("Email changed successfully.\n");
    } else {
        printf("Failed to change email. Incorrect old email or password.\n");
    }
}

int main() {
    User user = {"user@example.com", "password123"};
    char inputEmail[MAX_EMAIL_LENGTH];
    char inputPassword[MAX_PASSWORD_LENGTH];
    char newEmail[MAX_EMAIL_LENGTH];

    printf("Enter your current email: ");
    scanf("%s", inputEmail);
    printf("Enter your password: ");
    scanf("%s", inputPassword);

    if (login(&user, inputEmail, inputPassword)) {
        printf("Logged in successfully.\nEnter your old email: ");
        scanf("%s", inputEmail);
        printf("Enter your password again for confirmation: ");
        scanf("%s", inputPassword);
        printf("Enter your new email: ");
        scanf("%s", newEmail);

        changeEmail(&user, inputEmail, inputPassword, newEmail);
    } else {
        printf("Login failed. Incorrect email or password.\n");
    }

    return 0;
}