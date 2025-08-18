#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LENGTH 100
#define MAX_PASSWORD_LENGTH 50

typedef struct {
    char username[50];
    char email[MAX_EMAIL_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
} User;

void login(User *user) {
    char inputUsername[50], inputPassword[MAX_PASSWORD_LENGTH];

    printf("Enter Username: ");
    scanf("%49s", inputUsername);
    printf("Enter Password: ");
    scanf("%49s", inputPassword);

    if (strcmp(inputUsername, user->username) == 0 && strcmp(inputPassword, user->password) == 0) {
        printf("Login successful.\n");
        changeEmail(user);
    } else {
        printf("Invalid username or password. Please try again.\n");
    }
}

void changeEmail(User *user) {
    char newPassword[MAX_PASSWORD_LENGTH], newEmail[MAX_EMAIL_LENGTH];
    char confirmPassword[MAX_PASSWORD_LENGTH];

    printf("Enter New Email: ");
    scanf("%99s", newEmail);
    if (strcmp(newEmail, user->email) == 0) {
        printf("New email must be different from the current one.\n");
        return;
    }

    printf("Enter Password to confirm changes: ");
    scanf("%49s", confirmPassword);

    if (strcmp(confirmPassword, user->password) != 0) {
        printf("Incorrect password. Cannot change email.\n");
        return;
    }
    
    printf("Enter New Password: ");
    scanf("%49s", newPassword);

    strcpy(user->email, newEmail);
    strcpy(user->password, newPassword);

    printf("Email and password updated successfully!\n");
}

int main() {
    User user = {"user1", "user1@example.com", "pass123"};

    login(&user);

    return 0;
}