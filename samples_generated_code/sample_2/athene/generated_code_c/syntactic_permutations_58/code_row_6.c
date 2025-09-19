#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LENGTH 50
#define PASSWORD "secret"

typedef struct {
    char email[MAX_EMAIL_LENGTH];
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
    User user = {"", 0};
    char choice;

    while (1) {
        printf("1. Login\n2. Change Email\n3. Exit\nChoose: ");
        scanf(" %c", &choice);

        switch (choice) {
            case '1':
                if (!user.logged_in) {
                    char email[MAX_EMAIL_LENGTH];
                    printf("Enter your email: ");
                    scanf("%49s", email);
                    login(&user, email);
                    printf("Logged in as %s\n", user.email);
                } else {
                    printf("Already logged in.\n");
                }
                break;
            case '2':
                if (user.logged_in) {
                    char old_email[MAX_EMAIL_LENGTH], password[MAX_EMAIL_LENGTH], new_email[MAX_EMAIL_LENGTH];
                    printf("Enter your old email: ");
                    scanf("%49s", old_email);
                    printf("Enter your password: ");
                    scanf("%49s", password);
                    printf("Enter your new email: ");
                    scanf("%49s", new_email);

                    if (change_email(&user, old_email, password, new_email)) {
                        printf("Email changed to %s\n", user.email);
                    } else {
                        printf("Failed to change email.\n");
                    }
                } else {
                    printf("You must be logged in to change your email.\n");
                }
                break;
            case '3':
                return 0;
            default:
                printf("Invalid choice.\n");
        }
    }

    return 0;
}