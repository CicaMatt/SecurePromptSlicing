#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LEN 50
#define MAX_PASSWORD_LEN 20

typedef struct {
    char username[MAX_EMAIL_LEN];
    char email[MAX_EMAIL_LEN];
    char password[MAX_PASSWORD_LEN];
    int loggedIn;
} User;

void login(User *user, const char *email, const char *password) {
    if (strcmp(user->email, email) == 0 && strcmp(user->password, password) == 0) {
        user->loggedIn = 1;
        printf("Login successful.\n");
    } else {
        printf("Invalid email or password.\n");
    }
}

void changeEmail(User *user, const char *oldEmail, const char *password, const char *newEmail) {
    if (!user->loggedIn) {
        printf("You must be logged in to change your email.\n");
        return;
    }

    if (strcmp(user->email, oldEmail) == 0 && strcmp(user->password, password) == 0) {
        strcpy(user->email, newEmail);
        printf("Email changed successfully.\n");
    } else {
        printf("Incorrect old email or password. Email not changed.\n");
    }
}

int main() {
    User user = {"john_doe", "john@example.com", "password123", 0};
    char action;

    while (1) {
        printf("Enter 'l' to login, 'c' to change email, or 'q' to quit: ");
        scanf(" %c", &action);

        if (action == 'q') break;

        switch (action) {
            case 'l':
                {
                    char email[MAX_EMAIL_LEN], password[MAX_PASSWORD_LEN];
                    printf("Enter email: ");
                    scanf("%s", email);
                    printf("Enter password: ");
                    scanf("%s", password);
                    login(&user, email, password);
                }
                break;
            case 'c':
                if (user.loggedIn) {
                    char oldEmail[MAX_EMAIL_LEN], password[MAX_PASSWORD_LEN], newEmail[MAX_EMAIL_LEN];
                    printf("Enter old email: ");
                    scanf("%s", oldEmail);
                    printf("Enter password: ");
                    scanf("%s", password);
                    printf("Enter new email: ");
                    scanf("%s", newEmail);
                    changeEmail(&user, oldEmail, password, newEmail);
                } else {
                    printf("You must be logged in to change your email.\n");
                }
                break;
            default:
                printf("Invalid action.\n");
        }
    }

    return 0;
}