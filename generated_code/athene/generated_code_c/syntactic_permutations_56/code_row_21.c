#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LENGTH 50
#define MAX_PASSWORD_LENGTH 20

typedef struct {
    char email[MAX_EMAIL_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
} User;

void login(User *user) {
    char inputEmail[MAX_EMAIL_LENGTH];
    char inputPassword[MAX_PASSWORD_LENGTH];

    printf("Enter your email: ");
    scanf("%49s", inputEmail);
    printf("Enter your password: ");
    scanf("%19s", inputPassword);

    if (strcmp(inputEmail, user->email) == 0 && strcmp(inputPassword, user->password) == 0) {
        char oldEmail[MAX_EMAIL_LENGTH];
        char newEmail[MAX_EMAIL_LENGTH];
        char confirmPassword[MAX_PASSWORD_LENGTH];

        printf("Enter your current email: ");
        scanf("%49s", oldEmail);
        if (strcmp(oldEmail, user->email) != 0) {
            printf("Incorrect current email.\n");
            return;
        }

        printf("Enter your new email: ");
        scanf("%49s", newEmail);
        if (strcmp(newEmail, user->email) == 0) {
            printf("New email must be different from the old one.\n");
            return;
        }

        printf("Confirm your password: ");
        scanf("%19s", confirmPassword);
        if (strcmp(confirmPassword, user->password) != 0) {
            printf("Incorrect password.\n");
            return;
        }

        strcpy(user->email, newEmail);
        printf("Email changed successfully.\n");
    } else {
        printf("Login failed. Incorrect email or password.\n");
    }
}

int main() {
    User user = {"user@example.com", "password123"};

    login(&user);

    return 0;
}