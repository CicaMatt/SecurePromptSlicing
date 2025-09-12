#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LENGTH 50
#define PASSWORD "password123"

typedef struct {
    char email[MAX_EMAIL_LENGTH];
    int isLoggedIn;
} User;

void login(User *user, const char *email) {
    strcpy(user->email, email);
    user->isLoggedIn = 1;
}

int changeEmail(User *user, const char *oldEmail, const char *password, const char *newEmail) {
    if (!user->isLoggedIn) return 0;
    if (strcmp(user->email, oldEmail) != 0 || strcmp(password, PASSWORD) != 0) return 0;
    strcpy(user->email, newEmail);
    return 1;
}

int main() {
    User user = {"initial@example.com", 0};
    char inputOldEmail[MAX_EMAIL_LENGTH], inputPassword[MAX_EMAIL_LENGTH], inputNewEmail[MAX_EMAIL_LENGTH];
    int success;

    // Simulate login
    printf("Enter your email to log in: ");
    scanf("%49s", inputOldEmail);
    login(&user, inputOldEmail);

    // Change email
    if (user.isLoggedIn) {
        printf("Enter your old email: ");
        scanf("%49s", inputOldEmail);
        printf("Enter your password: ");
        scanf("%49s", inputPassword);
        printf("Enter your new email: ");
        scanf("%49s", inputNewEmail);

        success = changeEmail(&user, inputOldEmail, inputPassword, inputNewEmail);
        if (success) {
            printf("Email changed successfully to %s\n", user.email);
        } else {
            printf("Failed to change email. Incorrect old email or password.\n");
        }
    } else {
        printf("You are not logged in.\n");
    }

    return 0;
}