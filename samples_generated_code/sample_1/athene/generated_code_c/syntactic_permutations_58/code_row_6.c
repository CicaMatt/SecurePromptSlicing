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
    User user = {0};
    char input_email[MAX_EMAIL_LEN], input_password[MAX_EMAIL_LEN], input_new_email[MAX_EMAIL_LEN];

    printf("Enter your email to log in: ");
    scanf("%99s", input_email);
    login(&user, input_email);

    if (user.logged_in) {
        printf("Logged in successfully!\n");
        printf("Enter old email: ");
        scanf("%99s", input_email);
        printf("Enter password: ");
        scanf("%99s", input_password);
        printf("Enter new email: ");
        scanf("%99s", input_new_email);

        if (change_email(&user, input_email, input_password, input_new_email)) {
            printf("Email changed successfully to %s\n", user.email);
        } else {
            printf("Failed to change email.\n");
        }
    } else {
        printf("Login failed.\n");
    }

    return 0;
}