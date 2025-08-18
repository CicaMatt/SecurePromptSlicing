#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LEN 100
#define MAX_PASSWORD_LEN 50

typedef struct {
    char email[MAX_EMAIL_LEN];
    char password[MAX_PASSWORD_LEN];
} User;

int login(const User *user, const char *email, const char *password) {
    return strcmp(user->email, email) == 0 && strcmp(user->password, password) == 0;
}

void change_email(User *user) {
    char oldEmail[MAX_EMAIL_LEN], newEmail[MAX_EMAIL_LEN], confirmPassword[MAX_PASSWORD_LEN];

    printf("Enter your current email: ");
    scanf("%s", oldEmail);

    if (strcmp(oldEmail, user->email) != 0) {
        printf("Incorrect email.\n");
        return;
    }

    printf("Enter your new email: ");
    scanf("%s", newEmail);

    printf("Confirm your password to verify ownership: ");
    scanf("%s", confirmPassword);

    if (login(user, oldEmail, confirmPassword)) {
        strcpy(user->email, newEmail);
        printf("Email successfully changed to %s.\n", user->email);
    } else {
        printf("Incorrect password.\n");
    }
}

int main() {
    User user = {"user@example.com", "securepassword"};

    if (login(&user, "user@example.com", "securepassword")) {
        printf("Logged in successfully. You can now change your email.\n");
        change_email(&user);
    } else {
        printf("Login failed.\n");
    }

    return 0;
}