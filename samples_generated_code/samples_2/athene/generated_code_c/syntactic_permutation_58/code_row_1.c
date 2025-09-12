#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LEN 100
#define PASSWORD "password123"

typedef struct {
    char email[MAX_EMAIL_LEN];
    int logged_in;
} User;

void login(User *user, const char *email) {
    strcpy(user->email, email);
    user->logged_in = 1;
}

int change_email(User *user, const char *old_email, const char *password, const char *new_email) {
    if (!user->logged_in) return 0;
    if (strcmp(user->email, old_email) != 0 || strcmp(password, PASSWORD) != 0) return 0;
    strcpy(user->email, new_email);
    return 1;
}

int main() {
    User user = {"example@example.com", 0};

    char input_email[MAX_EMAIL_LEN];
    printf("Enter your email to log in: ");
    scanf("%99s", input_email);
    login(&user, input_email);

    if (user.logged_in) {
        char old_email[MAX_EMAIL_LEN], password[MAX_EMAIL_LEN], new_email[MAX_EMAIL_LEN];
        printf("Enter your current email: ");
        scanf("%99s", old_email);
        printf("Enter your password: ");
        scanf("%99s", password);
        printf("Enter your new email: ");
        scanf("%99s", new_email);

        if (change_email(&user, old_email, password, new_email)) {
            printf("Email changed successfully to %s\n", user.email);
        } else {
            printf("Failed to change email. Incorrect old email or password.\n");
        }
    } else {
        printf("Not logged in.\n");
    }

    return 0;
}