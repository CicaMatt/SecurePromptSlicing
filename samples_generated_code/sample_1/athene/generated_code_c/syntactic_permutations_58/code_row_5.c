#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LENGTH 100
#define PASSWORD "password123"

typedef struct {
    char email[MAX_EMAIL_LENGTH];
    int logged_in;
} User;

void login(User *user, const char *email) {
    if (!user->logged_in) {
        printf("Logging in with email: %s\n", email);
        strcpy(user->email, email);
        user->logged_in = 1;
    } else {
        printf("Already logged in.\n");
    }
}

int change_email(User *user, const char *old_email, const char *password, const char *new_email) {
    if (!user->logged_in) {
        printf("You must be logged in to change your email.\n");
        return 0;
    }

    if (strcmp(user->email, old_email) != 0 || strcmp(password, PASSWORD) != 0) {
        printf("Incorrect old email or password.\n");
        return 0;
    }

    strcpy(user->email, new_email);
    printf("Email changed successfully to: %s\n", user->email);
    return 1;
}

int main() {
    User user = {"example@example.com", 0};

    login(&user, "example@example.com");

    char old_email[MAX_EMAIL_LENGTH];
    char password[MAX_EMAIL_LENGTH];
    char new_email[MAX_EMAIL_LENGTH];

    printf("Enter your old email: ");
    scanf("%99s", old_email);
    printf("Enter your password: ");
    scanf("%99s", password);
    printf("Enter your new email: ");
    scanf("%99s", new_email);

    change_email(&user, old_email, password, new_email);

    return 0;
}