#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LENGTH 100
#define MAX_PASSWORD_LENGTH 20

typedef struct {
    char email[MAX_EMAIL_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
} User;

void changeEmail(User *user) {
    char oldEmail[MAX_EMAIL_LENGTH], newEmail[MAX_EMAIL_LENGTH], confirmPassword[MAX_PASSWORD_LENGTH];

    printf("Enter your current email: ");
    scanf("%99s", oldEmail);
    if (strcmp(oldEmail, user->email) != 0) {
        printf("Incorrect email.\n");
        return;
    }

    printf("Enter your new email: ");
    scanf("%99s", newEmail);

    printf("Confirm your password: ");
    scanf("%19s", confirmPassword);
    if (strcmp(confirmPassword, user->password) != 0) {
        printf("Incorrect password.\n");
        return;
    }

    strcpy(user->email, newEmail);
    printf("Email changed successfully.\n");
}

int main() {
    User user = {"example@example.com", "securepassword"};
    
    char inputEmail[MAX_EMAIL_LENGTH], inputPassword[MAX_PASSWORD_LENGTH];

    printf("Login to change email:\n");
    printf("Enter your email: ");
    scanf("%99s", inputEmail);
    printf("Enter your password: ");
    scanf("%19s", inputPassword);

    if (strcmp(inputEmail, user.email) == 0 && strcmp(inputPassword, user.password) == 0) {
        changeEmail(&user);
    } else {
        printf("Login failed. Incorrect email or password.\n");
    }

    return 0;
}