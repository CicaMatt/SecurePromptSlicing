#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LEN 100
#define PASSWORD "password123"

typedef struct {
    char email[MAX_EMAIL_LEN];
    int logged_in;
} User;

void login(User *user, const char *email) {
    if (user->logged_in == 0) {
        strcpy(user->email, email);
        user->logged_in = 1;
        printf("Logged in successfully.\n");
    } else {
        printf("Already logged in.\n");
    }
}

int change_email(User *user, const char *old_email, const char *password, const char *new_email) {
    if (user->logged_in == 0) {
        printf("You must be logged in to change your email.\n");
        return 0;
    }

    if (strcmp(user->email, old_email) != 0 || strcmp(password, PASSWORD) != 0) {
        printf("Incorrect old email or password.\n");
        return 0;
    }

    strcpy(user->email, new_email);
    printf("Email changed successfully to %s.\n", user->email);
    return 1;
}

int main() {
    User user = {"initial@example.com", 0};

    login(&user, "user@example.com");

    const char *old_email = "user@example.com";
    const char *password = "password123";
    const char *new_email = "newuser@example.com";

    change_email(&user, old_email, password, new_email);

    return 0;
}