#include <stdio.h>
#include <string.h>

#define MAX_LENGTH 100

typedef struct {
    char username[MAX_LENGTH];
    char oldEmail[MAX_LENGTH];
    char newPassword[MAX_LENGTH];
    char currentPassword[MAX_LENGTH];
} User;

void loginUser(User *user) {
    printf("Enter your username: ");
    fgets(user->username, MAX_LENGTH, stdin);
    user->username[strcspn(user->username, "\n")] = 0; // Remove newline character

    printf("Enter your password: ");
    fgets(user->currentPassword, MAX_LENGTH, stdin);
    user->currentPassword[strcspn(user->currentPassword, "\n")] = 0; // Remove newline character
}

int verifyCredentials(User *user) {
    char enteredOldEmail[MAX_LENGTH];
    char enteredCurrentPassword[MAX_LENGTH];

    printf("Enter your old email: ");
    fgets(enteredOldEmail, MAX_LENGTH, stdin);
    enteredOldEmail[strcspn(enteredOldEmail, "\n")] = 0; // Remove newline character

    printf("Confirm your password: ");
    fgets(enteredCurrentPassword, MAX_LENGTH, stdin);
    enteredCurrentPassword[strcspn(enteredCurrentPassword, "\n")] = 0; // Remove newline character

    if (strcmp(user->oldEmail, enteredOldEmail) == 0 && strcmp(user->currentPassword, enteredCurrentPassword) == 0) {
        return 1;
    } else {
        return 0;
    }
}

void changeEmail(User *user) {
    printf("Enter your new email: ");
    fgets(user->oldEmail, MAX_LENGTH, stdin);
    user->oldEmail[strcspn(user->oldEmail, "\n")] = 0; // Remove newline character
    printf("Your email has been changed to %s\n", user->oldEmail);
}

int main() {
    User user;
    
    strcpy(user.oldEmail, "example@example.com");
    strcpy(user.currentPassword, "password123");

    loginUser(&user);

    if (verifyCredentials(&user)) {
        changeEmail(&user);
    } else {
        printf("Incorrect old email or password. Email not changed.\n");
    }

    return 0;
}