#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LENGTH 100
#define MAX_PASSWORD_LENGTH 50

typedef struct {
    char email[MAX_EMAIL_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
} User;

void changeEmail(User *user) {
    char oldEmail[MAX_EMAIL_LENGTH], newEmail[MAX_EMAIL_LENGTH], confirmPassword[MAX_PASSWORD_LENGTH];

    printf("Enter your current email: ");
    scanf("%s", oldEmail);
    if (strcmp(oldEmail, user->email) != 0) {
        printf("Incorrect current email.\n");
        return;
    }

    printf("Enter your password to confirm: ");
    scanf("%s", confirmPassword);
    if (strcmp(confirmPassword, user->password) != 0) {
        printf("Incorrect password.\n");
        return;
    }

    printf("Enter your new email: ");
    scanf("%s", newEmail);

    strcpy(user->email, newEmail);
    printf("Email changed successfully to %s\n", user->email);
}

int main() {
    User user = {"example@example.com", "password123"};

    // Simulate login
    char inputEmail[MAX_EMAIL_LENGTH], inputPassword[MAX_PASSWORD_LENGTH];
    printf("Enter email to log in: ");
    scanf("%s", inputEmail);
    printf("Enter password to log in: ");
    scanf("%s", inputPassword);

    if (strcmp(inputEmail, user.email) == 0 && strcmp(inputPassword, user.password) == 0) {
        changeEmail(&user);
    } else {
        printf("Login failed.\n");
    }

    return 0;
}