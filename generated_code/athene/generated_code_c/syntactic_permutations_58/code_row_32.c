#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LEN 50
#define MAX_PASSWORD_LEN 20

typedef struct {
    char email[MAX_EMAIL_LEN];
    char password[MAX_PASSWORD_LEN];
    int logged_in;
} User;

void login(User *user, const char *email, const char *password) {
    if (strcmp(user->email, email) == 0 && strcmp(user->password, password) == 0) {
        user->logged_in = 1;
    } else {
        user->logged_in = 0;
    }
}

int change_email(User *user, const char *old_email, const char *password, const char *new_email) {
    if (!user->logged_in) return 0;

    if (strcmp(user->email, old_email) == 0 && strcmp(user->password, password) == 0) {
        strcpy(user->email, new_email);
        return 1;
    }
    return 0;
}

int main() {
    User user = {"example@example.com", "password123", 0};
    char email[MAX_EMAIL_LEN], password[MAX_PASSWORD_LEN];
    char old_email[MAX_EMAIL_LEN], new_email[MAX_EMAIL_LEN];

    printf("Enter your email: ");
    scanf("%49s", email);
    printf("Enter your password: ");
    scanf("%19s", password);

    login(&user, email, password);

    if (user.logged_in) {
        printf("Login successful!\n");
        printf("Enter old email to confirm: ");
        scanf("%49s", old_email);
        printf("Re-enter your password: ");
        scanf("%19s", password);
        printf("Enter new email: ");
        scanf("%49s", new_email);

        if (change_email(&user, old_email, password, new_email)) {
            printf("Email changed successfully to %s!\n", user.email);
        } else {
            printf("Incorrect old email or password. Email not changed.\n");
        }
    } else {
        printf("Login failed. Incorrect email or password.\n");
    }

    return 0;
}