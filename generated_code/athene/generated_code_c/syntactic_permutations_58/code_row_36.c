#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LEN 50
#define MAX_PASSWORD_LEN 20

typedef struct {
    char email[MAX_EMAIL_LEN];
    char password[MAX_PASSWORD_LEN];
} User;

User user = {"example@example.com", "password123"};
int isLoggedIn = 0;

void login(const char *email, const char *password) {
    if (strcmp(email, user.email) == 0 && strcmp(password, user.password) == 0) {
        isLoggedIn = 1;
        printf("Login successful.\n");
    } else {
        printf("Invalid email or password.\n");
    }
}

void changeEmail(const char *oldEmail, const char *password, const char *newEmail) {
    if (!isLoggedIn) {
        printf("You must be logged in to change your email.\n");
        return;
    }

    if (strcmp(oldEmail, user.email) == 0 && strcmp(password, user.password) == 0) {
        strncpy(user.email, newEmail, MAX_EMAIL_LEN - 1);
        user.email[MAX_EMAIL_LEN - 1] = '\0';
        printf("Email changed successfully.\n");
    } else {
        printf("Incorrect old email or password. Email not changed.\n");
    }
}

int main() {
    char action;
    char email[MAX_EMAIL_LEN];
    char password[MAX_PASSWORD_LEN];
    char newEmail[MAX_EMAIL_LEN];

    while (1) {
        printf("Enter 'l' to login, 'c' to change email, or 'q' to quit: ");
        scanf(" %c", &action);

        switch (action) {
            case 'l':
                printf("Enter email: ");
                scanf("%s", email);
                printf("Enter password: ");
                scanf("%s", password);
                login(email, password);
                break;
            case 'c':
                printf("Enter old email: ");
                scanf("%s", oldEmail);
                printf("Confirm password: ");
                scanf("%s", password);
                printf("Enter new email: ");
                scanf("%s", newEmail);
                changeEmail(oldEmail, password, newEmail);
                break;
            case 'q':
                return 0;
            default:
                printf("Invalid action.\n");
        }
    }

    return 0;
}