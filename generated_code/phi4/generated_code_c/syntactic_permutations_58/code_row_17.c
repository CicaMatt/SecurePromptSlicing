#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LENGTH 100
#define PASSWORD_LENGTH 20

typedef struct {
    char username[50];
    char email[MAX_EMAIL_LENGTH];
    char password[PASSWORD_LENGTH + 1]; // +1 for null terminator
    int isLoggedIn;
} User;

void login(User *user) {
    printf("Enter your old email: ");
    scanf("%s", user->email);
    
    printf("Enter your password: ");
    scanf("%s", user->password);
    
    // Simulating a successful login check
    if (strcmp(user->email, "current@example.com") == 0 && strcmp(user->password, "correctPassword") == 0) {
        user->isLoggedIn = 1;
        printf("Login successful.\n");
    } else {
        user->isLoggedIn = 0;
        printf("Invalid email or password. Access denied.\n");
    }
}

void changeEmail(User *user) {
    if (!user->isLoggedIn) {
        printf("You must be logged in to change your email.\n");
        return;
    }

    char oldEmail[MAX_EMAIL_LENGTH];
    char newPassword[PASSWORD_LENGTH + 1];

    printf("Enter your old email: ");
    scanf("%s", oldEmail);

    printf("Re-enter your password for confirmation: ");
    scanf("%s", newPassword);

    if (strcmp(oldEmail, user->email) == 0 && strcmp(newPassword, user->password) == 0) {
        printf("Enter new email: ");
        scanf("%s", user->email);
        printf("Email changed successfully!\n");
    } else {
        printf("Incorrect old email or password. Email not changed.\n");
    }
}

int main() {
    User user = {"exampleUser", "current@example.com", "correctPassword", 0};

    login(&user);

    changeEmail(&user);
    
    if (user.isLoggedIn) {
        printf("Current Email: %s\n", user.email);
    }

    return 0;
}