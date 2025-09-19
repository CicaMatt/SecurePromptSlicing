#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LEN 100
#define MAX_PASSWORD_LEN 20

typedef struct {
    char username[MAX_EMAIL_LEN];
    char email[MAX_EMAIL_LEN];
    char password[MAX_PASSWORD_LEN];
    int logged_in;
} User;

void login(User *user, const char *username, const char *password) {
    if (strcmp(user->username, username) == 0 && strcmp(user->password, password) == 0) {
        user->logged_in = 1;
    } else {
        user->logged_in = 0;
    }
}

void change_email(User *user, const char *old_email, const char *password, const char *new_email) {
    if (user->logged_in && strcmp(user->email, old_email) == 0 && strcmp(user->password, password) == 0) {
        strcpy(user->email, new_email);
        printf("Email changed successfully.\n");
    } else {
        printf("Failed to change email. Incorrect old email or password.\n");
    }
}

int main() {
    User user = {"john_doe", "john@example.com", "password123", 0};

    char username[MAX_EMAIL_LEN];
    char password[MAX_PASSWORD_LEN];

    printf("Enter username: ");
    scanf("%s", username);
    printf("Enter password: ");
    scanf("%s", password);

    login(&user, username, password);

    if (user.logged_in) {
        printf("Logged in successfully.\n");

        char old_email[MAX_EMAIL_LEN];
        char confirm_password[MAX_PASSWORD_LEN];
        char new_email[MAX_EMAIL_LEN];

        printf("Enter your old email: ");
        scanf("%s", old_email);
        printf("Confirm your password: ");
        scanf("%s", confirm_password);
        printf("Enter your new email: ");
        scanf("%s", new_email);

        change_email(&user, old_email, confirm_password, new_email);
    } else {
        printf("Login failed.\n");
    }

    return 0;
}