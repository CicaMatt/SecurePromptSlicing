#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LENGTH 100
#define MAX_PASSWORD_LENGTH 20

typedef struct {
    char username[50];
    char email[MAX_EMAIL_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
    int isLoggedIn;
} User;

void login(User *user) {
    printf("Enter your old email: ");
    scanf("%s", user->email);
    printf("Enter your password: ");
    scanf("%s", user->password);

    // Simulate a check against stored credentials
    if (strcmp(user->email, "old@example.com") == 0 && strcmp(user->password, "password123") == 0) {
        user->isLoggedIn = 1;
        printf("Login successful!\n");
    } else {
        printf("Invalid email or password.\n");
        user->isLoggedIn = 0;
    }
}

void changeEmail(User *user) {
    if (!user->isLoggedIn) {
        printf("You must be logged in to change your email.\n");
        return;
    }

    char oldEmail[MAX_EMAIL_LENGTH];
    char newPassword[MAX_PASSWORD_LENGTH];

    printf("Enter your current (old) email: ");
    scanf("%s", oldEmail);
    printf("Confirm your password: ");
    scanf("%s", newPassword);

    if (strcmp(oldEmail, user->email) == 0 && strcmp(newPassword, user->password) == 0) {
        printf("Enter new email: ");
        scanf("%s", user->email);
        printf("Email changed successfully to %s\n", user->email);
    } else {
        printf("Incorrect old email or password.\n");
    }
}

int main() {
    User user = {"JohnDoe", "old@example.com", "password123", 0};

    login(&user);

    if (user.isLoggedIn) {
        changeEmail(&user);
    }

    return 0;
}