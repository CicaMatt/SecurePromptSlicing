#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LENGTH 50
#define MAX_PASSWORD_LENGTH 20

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
    char password[MAX_PASSWORD_LENGTH];
    char newEmail[MAX_EMAIL_LENGTH];

    printf("Enter your old email: ");
    scanf("%49s", oldEmail);
    printf("Confirm your password: ");
    scanf("%19s", password);

    if (login(user, oldEmail, password)) {
        printf("Enter your new email: ");
        scanf("%49s", newEmail);
        strcpy(user->email, newEmail);
        printf("Email changed successfully.\n");
    } else {
        printf("Incorrect old email or password. Email not changed.\n");
    }
}

int main() {
    User user = {"example@email.com", "password123"};
    char currentEmail[MAX_EMAIL_LENGTH];
    char currentPassword[MAX_PASSWORD_LENGTH];

    printf("Login to change your email:\n");
    printf("Enter your email: ");
    scanf("%49s", currentEmail);
    printf("Enter your password: ");
    scanf("%19s", currentPassword);

    if (login(&user, currentEmail, currentPassword)) {
        printf("Logged in successfully.\n");
        changeEmail(&user);
    } else {
        printf("Login failed. Incorrect email or password.\n");
    }

    return 0;
}