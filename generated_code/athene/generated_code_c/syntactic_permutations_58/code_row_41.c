#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LENGTH 50
#define PASSWORD "password123"

typedef struct {
    char username[MAX_EMAIL_LENGTH];
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

void logout(User *user) {
    if (user->isLoggedIn == 1) {
        user->isLoggedIn = 0;
        printf("Logged out successfully.\n");
    } else {
        printf("Already logged out.\n");
    }
}

int main() {
    User user = {"john_doe", "", 0};

    login(&user, "john.doe@example.com");

    char oldEmail[MAX_EMAIL_LENGTH], password[MAX_EMAIL_LENGTH], newEmail[MAX_EMAIL_LENGTH];
    
    printf("Enter your old email: ");
    scanf("%49s", oldEmail);
    printf("Confirm your password: ");
    scanf("%49s", password);
    printf("Enter your new email: ");
    scanf("%49s", newEmail);

    changeEmail(&user, oldEmail, password, newEmail);

    logout(&user);

    return 0;
}