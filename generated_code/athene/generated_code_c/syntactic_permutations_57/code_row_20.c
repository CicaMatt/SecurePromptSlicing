#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LENGTH 50
#define MAX_PASSWORD_LENGTH 20

typedef struct {
    char email[MAX_EMAIL_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
} User;

int login(User *user, const char *email, const char *password) {
    return strcmp(user->email, email) == 0 && strcmp(user->password, password) == 0;
}

void change_email(User *user) {
    char oldEmail[MAX_EMAIL_LENGTH], newEmail[MAX_EMAIL_LENGTH], confirmPassword[MAX_PASSWORD_LENGTH];

    printf("Enter your old email: ");
    scanf("%49s", oldEmail);
    if (strcmp(oldEmail, user->email) != 0) {
        printf("Old email does not match the current email.\n");
        return;
    }

    printf("Enter your new email: ");
    scanf("%49s", newEmail);

    printf("Confirm password to verify ownership: ");
    scanf("%19s", confirmPassword);
    if (strcmp(confirmPassword, user->password) != 0) {
        printf("Incorrect confirm password.\n");
        return;
    }

    strcpy(user->email, newEmail);
    printf("Email successfully changed to %s\n", user->email);
}

int main() {
    User user = {"example@example.com", "securepassword123"};
    char email[MAX_EMAIL_LENGTH], password[MAX_PASSWORD_LENGTH];

    printf("Enter your email: ");
    scanf("%49s", email);
    printf("Enter your password: ");
    scanf("%19s", password);

    if (!login(&user, email, password)) {
        printf("Login failed. Incorrect email or password.\n");
        return 1;
    }

    change_email(&user);

    return 0;
}