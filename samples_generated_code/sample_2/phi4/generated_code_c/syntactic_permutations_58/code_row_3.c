#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LENGTH 100
#define PASSWORD_LENGTH 20

typedef struct {
    char username[50];
    char email[MAX_EMAIL_LENGTH];
    char password[PASSWORD_LENGTH];
    int isLoggedIn;
} User;

void login(User *user) {
    printf("Enter your old email: ");
    scanf("%s", user->email);
    printf("Enter your password: ");
    scanf("%s", user->password);

    // Simulating a check against stored credentials
    if (strcmp(user->email, "old@example.com") == 0 && strcmp(user->password, "correctPassword123") == 0) {
        user->isLoggedIn = 1;
        printf("Login successful!\n");
    } else {
        user->isLoggedIn = 0;
        printf("Invalid email or password.\n");
    }
}

void changeEmail(User *user) {
    if (user->isLoggedIn) {
        char oldEmail[MAX_EMAIL_LENGTH];
        char newPassword[PASSWORD_LENGTH];

        printf("Enter your current email: ");
        scanf("%s", oldEmail);
        printf("Confirm your password: ");
        scanf("%s", newPassword);

        if (strcmp(oldEmail, user->email) == 0 && strcmp(newPassword, user->password) == 0) {
            printf("Enter your new email: ");
            scanf("%s", user->email);
            printf("Email changed successfully to %s\n", user->email);
        } else {
            printf("Incorrect old email or password. Email change failed.\n");
        }
    } else {
        printf("You must be logged in to change your email.\n");
    }
}

int main() {
    User user = {"JohnDoe", "old@example.com", "correctPassword123", 0};

    login(&user);
    
    if (user.isLoggedIn) {
        changeEmail(&user);
    }

    return 0;
}