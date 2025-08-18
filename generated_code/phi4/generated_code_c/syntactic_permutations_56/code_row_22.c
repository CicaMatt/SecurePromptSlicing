#include <stdio.h>
#include <string.h>

#define MAX_LEN 100

typedef struct {
    char username[MAX_LEN];
    char password[MAX_LEN];
    char email[MAX_LEN];
} User;

void login(User* user, const char* inputUsername, const char* inputPassword) {
    if (strcmp(user->username, inputUsername) == 0 && strcmp(user->password, inputPassword) == 0) {
        printf("Login successful!\n");
    } else {
        printf("Invalid username or password. Please try again.\n");
        exit(1);
    }
}

void changeEmail(User* user, const char* newPassword, const char* newEmail) {
    if (strcmp(user->password, newPassword) != 0) {
        printf("Incorrect password. Unable to change email.\n");
        return;
    }

    if (strcmp(user->email, newEmail) == 0) {
        printf("The new email must be different from the current one.\n");
        return;
    }
    
    strcpy(user->email, newEmail);
    printf("Email changed successfully!\n");
}

int main() {
    User user = {"user1", "password123", "user1@example.com"};
    char inputUsername[MAX_LEN];
    char inputPassword[MAX_LEN];
    char newPassword[MAX_LEN];
    char confirmNewPassword[MAX_LEN];
    char newEmail[MAX_LEN];

    printf("Enter username: ");
    scanf("%s", inputUsername);

    printf("Enter password: ");
    scanf("%s", inputPassword);
    
    login(&user, inputUsername, inputPassword);

    printf("Enter your current password to change email: ");
    scanf("%s", newPassword);

    printf("Confirm new password: ");
    scanf("%s", confirmNewPassword);

    if (strcmp(newPassword, confirmNewPassword) != 0) {
        printf("Passwords do not match. Unable to change email.\n");
        return 1;
    }

    printf("Enter your new email address: ");
    scanf("%s", newEmail);

    changeEmail(&user, newPassword, newEmail);

    return 0;
}