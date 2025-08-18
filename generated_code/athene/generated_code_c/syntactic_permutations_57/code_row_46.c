#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LENGTH 256
#define MAX_PASSWORD_LENGTH 32

typedef struct {
    char email[MAX_EMAIL_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
} User;

int authenticate(const User *user, const char *email, const char *password) {
    return strcmp(user->email, email) == 0 && strcmp(user->password, password) == 0;
}

void change_email(User *user, const char *oldEmail, const char *newEmail, const char *confirmPassword) {
    if (authenticate(user, oldEmail, confirmPassword)) {
        strncpy(user->email, newEmail, MAX_EMAIL_LENGTH - 1);
        user->email[MAX_EMAIL_LENGTH - 1] = '\0';
        printf("Email changed successfully.\n");
    } else {
        printf("Authentication failed. Email or password is incorrect.\n");
    }
}

int main() {
    User loggedInUser = {"example@example.com", "password123"};
    char oldEmail[MAX_EMAIL_LENGTH];
    char newEmail[MAX_EMAIL_LENGTH];
    char confirmPassword[MAX_PASSWORD_LENGTH];

    printf("Enter your current email: ");
    scanf("%255s", oldEmail);
    printf("Enter your new email: ");
    scanf("%255s", newEmail);
    printf("Confirm your password: ");
    scanf("%31s", confirmPassword);

    change_email(&loggedInUser, oldEmail, newEmail, confirmPassword);

    return 0;
}