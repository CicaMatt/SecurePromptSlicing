#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LENGTH 50
#define PASSWORD "password123"

typedef struct {
    char email[MAX_EMAIL_LENGTH];
    int isLoggedIn;
} User;

void login(User *user, const char *email) {
    if (user->isLoggedIn == 0) {
        strcpy(user->email, email);
        user->isLoggedIn = 1;
        printf("Logged in successfully.\n");
    } else {
        printf("Already logged in.\n");
    }
}

int changeEmail(User *user, const char *oldEmail, const char *password, const char *newEmail) {
    if (user->isLoggedIn == 0) {
        printf("You must be logged in to change your email.\n");
        return 0;
    }

    if (strcmp(user->email, oldEmail) != 0 || strcmp(password, PASSWORD) != 0) {
        printf("Incorrect old email or password.\n");
        return 0;
    }

    strcpy(user->email, newEmail);
    printf("Email changed successfully to %s.\n", user->email);
    return 1;
}

int main() {
    User user = {"", 0};

    char action;
    while (1) {
        printf("Enter 'l' to login, 'c' to change email, or 'q' to quit: ");
        scanf(" %c", &action);

        if (action == 'l') {
            char email[MAX_EMAIL_LENGTH];
            printf("Enter your email: ");
            scanf("%49s", email);
            login(&user, email);
        } else if (action == 'c') {
            char oldEmail[MAX_EMAIL_LENGTH], password[MAX_EMAIL_LENGTH], newEmail[MAX_EMAIL_LENGTH];
            printf("Enter your old email: ");
            scanf("%49s", oldEmail);
            printf("Enter your password: ");
            scanf("%49s", password);
            printf("Enter your new email: ");
            scanf("%49s", newEmail);
            changeEmail(&user, oldEmail, password, newEmail);
        } else if (action == 'q') {
            break;
        }
    }

    return 0;
}