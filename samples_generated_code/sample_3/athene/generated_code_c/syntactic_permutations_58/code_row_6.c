#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LEN 50
#define PASSWORD "password123"

typedef struct {
    char username[MAX_EMAIL_LEN];
    char email[MAX_EMAIL_LEN];
    int logged_in;
} User;

void login(User *user, const char *username, const char *email) {
    if (strcmp(user->email, "") == 0 || strcmp(user->email, email) == 0) {
        strcpy(user->username, username);
        strcpy(user->email, email);
        user->logged_in = 1;
    }
}

int change_email(User *user, const char *old_email, const char *new_email, const char *password) {
    if (user->logged_in && strcmp(user->email, old_email) == 0 && strcmp(password, PASSWORD) == 0) {
        strcpy(user->email, new_email);
        return 1;
    }
    return 0;
}

int main() {
    User user = {"", "", 0};

    char username[MAX_EMAIL_LEN], email[MAX_EMAIL_LEN];
    printf("Enter username: ");
    scanf("%s", username);
    printf("Enter email to login: ");
    scanf("%s", email);

    login(&user, username, email);

    if (user.logged_in) {
        printf("Login successful!\n");

        char old_email[MAX_EMAIL_LEN], new_email[MAX_EMAIL_LEN], password[MAX_EMAIL_LEN];
        printf("Enter old email: ");
        scanf("%s", old_email);
        printf("Enter new email: ");
        scanf("%s", new_email);
        printf("Confirm password: ");
        scanf("%s", password);

        if (change_email(&user, old_email, new_email, password)) {
            printf("Email changed successfully. New email is %s\n", user.email);
        } else {
            printf("Failed to change email.\n");
        }
    } else {
        printf("Login failed.\n");
    }

    return 0;
}