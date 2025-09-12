#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LENGTH 50
#define PASSWORD "secret123"

typedef struct {
    char email[MAX_EMAIL_LENGTH];
    int logged_in;
} User;

void login(User *user, const char *email) {
    if (!user->logged_in) {
        strcpy(user->email, email);
        user->logged_in = 1;
        printf("Logged in as %s\n", user->email);
    } else {
        printf("Already logged in.\n");
    }
}

void change_email(User *user, const char *old_email, const char *password, const char *new_email) {
    if (user->logged_in && strcmp(user->email, old_email) == 0 && strcmp(password, PASSWORD) == 0) {
        strcpy(user->email, new_email);
        printf("Email changed to %s\n", user->email);
    } else {
        printf("Failed to change email. Please check your credentials.\n");
    }
}

int main() {
    User user = {"", 0};
    char input_email[MAX_EMAIL_LENGTH];
    char old_email[MAX_EMAIL_LENGTH], new_email[MAX_EMAIL_LENGTH];
    char password[MAX_EMAIL_LENGTH];

    printf("Enter your email to log in: ");
    scanf("%49s", input_email);
    login(&user, input_email);

    if (user.logged_in) {
        printf("Enter your current email: ");
        scanf("%49s", old_email);
        printf("Confirm your password: ");
        scanf("%49s", password);
        printf("Enter your new email: ");
        scanf("%49s", new_email);
        change_email(&user, old_email, password, new_email);
    }

    return 0;
}