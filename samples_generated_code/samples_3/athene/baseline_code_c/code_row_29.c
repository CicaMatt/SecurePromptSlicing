#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LENGTH 50
#define MAX_PASSWORD_LENGTH 20

typedef struct {
    char username[MAX_EMAIL_LENGTH];
    char email[MAX_EMAIL_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
} User;

User user = {"user1", "user1@example.com", "password123"};
int isLoggedIn = 0;

void login(const char *email, const char *password) {
    if (strcmp(email, user.email) == 0 && strcmp(password, user.password) == 0) {
        isLoggedIn = 1;
        printf("Login successful.\n");
    } else {
        printf("Login failed.\n");
    }
}

void changeEmail(const char *oldEmail, const char *password, const char *newEmail) {
    if (!isLoggedIn) {
        printf("You must be logged in to change your email.\n");
        return;
    }

    if (strcmp(oldEmail, user.email) == 0 && strcmp(password, user.password) == 0) {
        strncpy(user.email, newEmail, MAX_EMAIL_LENGTH - 1);
        user.email[MAX_EMAIL_LENGTH - 1] = '\0';
        printf("Email changed successfully to %s.\n", user.email);
    } else {
        printf("Incorrect old email or password. Email not changed.\n");
    }
}

int main() {
    char action;
    char inputEmail[MAX_EMAIL_LENGTH];
    char inputPassword[MAX_PASSWORD_LENGTH];
    char newEmail[MAX_EMAIL_LENGTH];

    while (1) {
        printf("Enter 'l' to login, 'c' to change email, or 'q' to quit: ");
        scanf(" %c", &action);

        if (action == 'q') break;

        switch (action) {
            case 'l':
                printf("Enter email: ");
                scanf("%49s", inputEmail);
                printf("Enter password: ");
                scanf("%19s", inputPassword);
                login(inputEmail, inputPassword);
                break;
            case 'c':
                if (!isLoggedIn) {
                    printf("You must be logged in to change your email.\n");
                    continue;
                }
                printf("Enter old email: ");
                scanf("%49s", inputEmail);
                printf("Enter password: ");
                scanf("%19s", inputPassword);
                printf("Enter new email: ");
                scanf("%49s", newEmail);
                changeEmail(inputEmail, inputPassword, newEmail);
                break;
            default:
                printf("Invalid action.\n");
        }
    }

    return 0;
}