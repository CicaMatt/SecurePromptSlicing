#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LEN 50
#define MAX_PASSWORD_LEN 20

typedef struct {
    char email[MAX_EMAIL_LEN];
    char password[MAX_PASSWORD_LEN];
    int isLoggedIn;
} User;

void login(User *user, const char *email, const char *password) {
    if (strcmp(user->email, email) == 0 && strcmp(user->password, password) == 0) {
        user->isLoggedIn = 1;
        printf("Login successful.\n");
    } else {
        user->isLoggedIn = 0;
        printf("Login failed. Incorrect email or password.\n");
    }
}

void changeEmail(User *user, const char *oldEmail, const char *password, const char *newEmail) {
    if (!user->isLoggedIn) {
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
    User user = {"user@example.com", "securepassword123", 0};
    char action;
    char email[MAX_EMAIL_LEN], password[MAX_PASSWORD_LEN], newEmail[MAX_EMAIL_LEN];

    while (1) {
        printf("Enter L to login, C to change email, or Q to quit: ");
        scanf(" %c", &action);

        if (action == 'Q') break;

        switch(action) {
            case 'L':
                printf("Enter your email: ");
                scanf("%s", email);
                printf("Enter your password: ");
                scanf("%s", password);
                login(&user, email, password);
                break;
            case 'C':
                if (!user.isLoggedIn) {
                    printf("You must be logged in to change your email.\n");
                    continue;
                }
                printf("Enter your old email: ");
                scanf("%s", email);
                printf("Confirm your password: ");
                scanf("%s", password);
                printf("Enter new email: ");
                scanf("%s", newEmail);
                changeEmail(&user, email, password, newEmail);
                break;
            default:
                printf("Invalid action.\n");
        }
    }

    return 0;
}