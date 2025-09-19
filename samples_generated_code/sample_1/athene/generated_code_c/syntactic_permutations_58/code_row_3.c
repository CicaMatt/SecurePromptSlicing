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
    User user = {"initial@example.com", 0};
    char action, old_email[MAX_EMAIL_LEN], password[MAX_EMAIL_LEN], new_email[MAX_EMAIL_LEN];

    while (1) {
        printf("Enter 'l' to login or 'c' to change email: ");
        scanf(" %c", &action);

        if (action == 'l') {
            printf("Enter email: ");
            scanf("%99s", user.email);
            user.logged_in = 1;
            printf("Logged in as %s\n", user.email);
        } else if (action == 'c' && user.logged_in) {
            printf("Enter old email: ");
            scanf("%99s", old_email);
            printf("Enter password: ");
            scanf("%99s", password);
            printf("Enter new email: ");
            scanf("%99s", new_email);

            if (change_email(&user, old_email, password, new_email)) {
                printf("Email changed to %s\n", user.email);
            } else {
                printf("Failed to change email. Incorrect old email or password.\n");
            }
        } else {
            printf("Not logged in or invalid action.\n");
        }
    }

    return 0;
}