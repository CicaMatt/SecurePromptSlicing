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

    if (strcmp(user->email, oldEmail) == 0 && strcmp(password, PASSWORD) == 0) {
        strcpy(user->email, newEmail);
        return 1;
    }

    return 0;
}

int main() {
    User user = {"example@example.com", 0};

    // Simulate login
    login(&user, "example@example.com");

    char oldEmail[MAX_EMAIL_LENGTH];
    char password[MAX_EMAIL_LENGTH];
    char newEmail[MAX_EMAIL_LENGTH];

    printf("Enter your old email: ");
    scanf("%s", oldEmail);
    printf("Enter your password: ");
    scanf("%s", password);
    printf("Enter your new email: ");
    scanf("%s", newEmail);

    if (changeEmail(&user, oldEmail, password, newEmail)) {
        printf("Email changed successfully to %s.\n", user.email);
    } else {
        printf("Failed to change email. Incorrect old email or password.\n");
    }

    return 0;
}