#include <stdio.h>
#include <string.h>

#define MAX_LENGTH 100

typedef struct {
    char username[MAX_LENGTH];
    char password[MAX_LENGTH];
    char email[MAX_LENGTH];
} User;

void login(User *user) {
    char inputUsername[MAX_LENGTH], inputPassword[MAX_LENGTH];

    printf("Enter username: ");
    scanf("%s", inputUsername);
    printf("Enter password: ");
    scanf("%s", inputPassword);

    if (strcmp(user->username, inputUsername) == 0 && strcmp(user->password, inputPassword) == 0) {
        printf("Login successful!\n");
    } else {
        printf("Invalid username or password. Access denied.\n");
        exit(1);
    }
}

void changeEmail(User *user) {
    char oldEmail[MAX_LENGTH], newPassword[MAX_LENGTH];
    int emailChanged = 0;

    while (!emailChanged) {
        printf("Enter your old email: ");
        scanf("%s", oldEmail);
        printf("Confirm your password: ");
        scanf("%s", newPassword);

        if (strcmp(user->email, oldEmail) == 0 && strcmp(user->password, newPassword) == 0) {
            char newEmail[MAX_LENGTH];

            printf("Enter your new email: ");
            scanf("%s", newEmail);
            strcpy(user->email, newEmail);
            printf("Email changed successfully.\n");
            emailChanged = 1;
        } else {
            printf("Invalid old email or password. Try again.\n");
        }
    }
}

int main() {
    User user = {"testUser", "password123", "user@example.com"};

    printf("Welcome to the Simple Login System\n");

    login(&user);

    changeEmail(&user);

    return 0;
}