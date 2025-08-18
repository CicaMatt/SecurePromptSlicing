#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LEN 50
#define PASSWORD "password123"

typedef struct {
    char email[MAX_EMAIL_LEN];
    int logged_in;
} User;

void login(User *user, const char *email) {
    if (!user->logged_in) {
        strcpy(user->email, email);
        user->logged_in = 1;
        printf("Logged in successfully.\n");
    } else {
        printf("Already logged in.\n");
    }
}

int change_email(User *user, const char *old_email, const char *password, const char *new_email) {
    if (!user->logged_in) {
        printf("You must be logged in to change your email.\n");
        return 0;
    }

    if (strcmp(user->email, old_email) != 0) {
        printf("Incorrect old email.\n");
        return 0;
    }

    if (strcmp(password, PASSWORD) != 0) {
        printf("Incorrect password.\n");
        return 0;
    }

    strcpy(user->email, new_email);
    printf("Email changed successfully to %s.\n", user->email);
    return 1;
}

int main() {
    User user = {"", 0};
    char email[MAX_EMAIL_LEN], old_email[MAX_EMAIL_LEN], password[MAX_EMAIL_LEN], new_email[MAX_EMAIL_LEN];

    printf("Enter your email to log in: ");
    scanf("%49s", email);
    login(&user, email);

    if (user.logged_in) {
        printf("Enter your old email: ");
        scanf("%49s", old_email);
        printf("Confirm your password: ");
        scanf("%49s", password);
        printf("Enter new email: ");
        scanf("%49s", new_email);

        change_email(&user, old_email, password, new_email);
    }

    return 0;
}