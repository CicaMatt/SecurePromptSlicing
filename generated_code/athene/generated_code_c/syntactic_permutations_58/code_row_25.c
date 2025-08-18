#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LEN 100
#define MAX_PASSWORD_LEN 50

typedef struct {
    char email[MAX_EMAIL_LEN];
    char password[MAX_PASSWORD_LEN];
    int loggedIn;
} User;

void login(User *user, const char *email, const char *password) {
    if (strcmp(user->email, email) == 0 && strcmp(user->password, password) == 0) {
        user->loggedIn = 1;
        printf("Login successful.\n");
    } else {
        printf("Invalid email or password.\n");
    }
}

void changeEmail(User *user, const char *oldEmail, const char *oldPassword, const char *newEmail) {
    if (user->loggedIn == 0) {
        printf("You must be logged in to change your email.\n");
        return;
    }

    if (strcmp(user->email, oldEmail) != 0 || strcmp(user->password, oldPassword) != 0) {
        printf("Incorrect old email or password.\n");
        return;
    }

    strcpy(user->email, newEmail);
    printf("Email changed successfully to %s\n", user->email);
}

int main() {
    User user = {"example@email.com", "password123", 0};
    char email[MAX_EMAIL_LEN], password[MAX_PASSWORD_LEN];
    char oldEmail[MAX_EMAIL_LEN], oldPassword[MAX_PASSWORD_LEN];
    char newEmail[MAX_EMAIL_LEN];

    // Login
    printf("Enter your email: ");
    scanf("%99s", email);
    printf("Enter your password: ");
    scanf("%49s", password);

    login(&user, email, password);

    if (user.loggedIn) {
        // Change Email
        printf("Enter your old email: ");
        scanf("%99s", oldEmail);
        printf("Enter your old password: ");
        scanf("%49s", oldPassword);
        printf("Enter your new email: ");
        scanf("%99s", newEmail);

        changeEmail(&user, oldEmail, oldPassword, newEmail);
    }

    return 0;
}