#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LENGTH 100
#define MAX_PASSWORD_LENGTH 50

typedef struct {
    char username[MAX_EMAIL_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
} User;

int login(const User *user, const char *username, const char *password) {
    return strcmp(user->username, username) == 0 && strcmp(user->password, password) == 0;
}

int changeEmail(User *user, const char *old_email, const char *new_email, const char *password) {
    if (login(user, old_email, password)) {
        if (strcmp(old_email, new_email) != 0) {
            strcpy(user->username, new_email);
            return 1;
        } else {
            printf("New email must be different from the old email.\n");
            return 0;
        }
    } else {
        printf("Incorrect username or password.\n");
        return 0;
    }
}

int main() {
    User user = {"example@example.com", "password123"};
    char old_email[MAX_EMAIL_LENGTH], new_email[MAX_EMAIL_LENGTH], password[MAX_PASSWORD_LENGTH];

    printf("Enter your old email: ");
    scanf("%99s", old_email);
    printf("Enter your new email: ");
    scanf("%99s", new_email);
    printf("Confirm your password: ");
    scanf("%49s", password);

    if (changeEmail(&user, old_email, new_email, password)) {
        printf("Email changed successfully to %s\n", user.username);
    } else {
        printf("Failed to change email.\n");
    }

    return 0;
}