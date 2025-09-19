#include <stdio.h>
#include <string.h>

#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 20
#define MAX_EMAIL_LENGTH 100

typedef struct {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
    char email[MAX_EMAIL_LENGTH];
    int isLoggedIn;
} User;

void login(User *user) {
    char inputUsername[MAX_USERNAME_LENGTH];
    char inputPassword[MAX_PASSWORD_LENGTH];

    printf("Enter username: ");
    scanf("%s", inputUsername);
    printf("Enter password: ");
    scanf("%s", inputPassword);

    if (strcmp(inputUsername, user->username) == 0 && strcmp(inputPassword, user->password) == 0) {
        user->isLoggedIn = 1;
        printf("Login successful!\n");
    } else {
        printf("Login failed.\n");
    }
}

void changeEmail(User *user) {
    if (!user->isLoggedIn) {
        printf("You must be logged in to change your email.\n");
        return;
    }

    char oldEmail[MAX_EMAIL_LENGTH];
    char confirmPassword[MAX_PASSWORD_LENGTH];

    printf("Enter old email: ");
    scanf("%s", oldEmail);
    printf("Confirm password: ");
    scanf("%s", confirmPassword);

    if (strcmp(oldEmail, user->email) == 0 && strcmp(confirmPassword, user->password) == 0) {
        char newEmail[MAX_EMAIL_LENGTH];
        printf("Enter new email: ");
        scanf("%s", newEmail);
        strcpy(user->email, newEmail);
        printf("Email changed successfully!\n");
    } else {
        printf("Incorrect old email or password. Email not changed.\n");
    }
}

int main() {
    User user = {"user1", "pass123", "user1@example.com", 0};

    while (1) {
        int choice;
        printf("1. Login\n2. Change Email\n3. Exit\nChoose an option: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                login(&user);
                break;
            case 2:
                changeEmail(&user);
                break;
            case 3:
                return 0;
            default:
                printf("Invalid choice. Try again.\n");
        }
    }

    return 0;
}