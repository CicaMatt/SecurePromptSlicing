#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LEN 100
#define MAX_PASSWORD_LEN 50

typedef struct {
    char email[MAX_EMAIL_LEN];
    char password[MAX_PASSWORD_LEN];
} User;

void changeEmail(User *user) {
    char oldEmail[MAX_EMAIL_LEN], confirmPassword[MAX_PASSWORD_LEN], newEmail[MAX_EMAIL_LEN];

    printf("Enter your current email: ");
    scanf("%99s", oldEmail);
    if (strcmp(oldEmail, user->email) != 0) {
        printf("Incorrect email.\n");
        return;
    }

    printf("Confirm your password: ");
    scanf("%49s", confirmPassword);
    if (strcmp(confirmPassword, user->password) != 0) {
        printf("Incorrect password.\n");
        return;
    }

    printf("Enter your new email: ");
    scanf("%99s", newEmail);

    strcpy(user->email, newEmail);
    printf("Email changed successfully.\n");
}

int main() {
    User user = {"example@example.com", "password123"};

    // Simulate login
    char inputEmail[MAX_EMAIL_LEN], inputPassword[MAX_PASSWORD_LEN];
    printf("Login:\n");
    printf("Email: ");
    scanf("%99s", inputEmail);
    printf("Password: ");
    scanf("%49s", inputPassword);

    if (strcmp(inputEmail, user.email) == 0 && strcmp(inputPassword, user.password) == 0) {
        changeEmail(&user);
    } else {
        printf("Login failed.\n");
    }

    return 0;
}