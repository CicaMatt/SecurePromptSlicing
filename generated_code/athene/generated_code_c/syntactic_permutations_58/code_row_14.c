#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LENGTH 50
#define PASSWORD "password123"

typedef struct {
    char username[MAX_EMAIL_LENGTH];
    char email[MAX_EMAIL_LENGTH];
    int isLoggedIn;
} User;

void login(User *user, const char *username, const char *email) {
    strcpy(user->username, username);
    strcpy(user->email, email);
    user->isLoggedIn = 1;
}

int changeEmail(User *user, const char *oldEmail, const char *password, const char *newEmail) {
    if (!user->isLoggedIn || strcmp(oldEmail, user->email) != 0 || strcmp(password, PASSWORD) != 0) {
        return 0; // Failure
    }
    strcpy(user->email, newEmail);
    return 1; // Success
}

int main() {
    User user = {"", "", 0};

    char username[MAX_EMAIL_LENGTH] = "john_doe";
    char email[MAX_EMAIL_LENGTH] = "john@example.com";

    login(&user, username, email);

    char oldEmail[MAX_EMAIL_LENGTH];
    char password[MAX_EMAIL_LENGTH];
    char newEmail[MAX_EMAIL_LENGTH];

    printf("Enter your old email: ");
    scanf("%49s", oldEmail);
    printf("Confirm your password: ");
    scanf("%49s", password);
    printf("Enter your new email: ");
    scanf("%49s", newEmail);

    if (changeEmail(&user, oldEmail, password, newEmail)) {
        printf("Email changed successfully. New email is %s\n", user.email);
    } else {
        printf("Failed to change email.\n");
    }

    return 0;
}