#include <stdio.h>
#include <string.h>

#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 50

typedef struct {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
} User;

int authenticateUser(const User *database, const char *inputUsername, const char *inputPassword) {
    return strcmp(database->username, inputUsername) == 0 && strcmp(database->password, inputPassword) == 0;
}

void redirectToDashboard() {
    printf("Redirecting to Dashboard...\n");
}

void redirectBackToLogin() {
    printf("Invalid credentials. Redirecting back to Login Page...\n");
}

int main() {
    User database = {"admin", "password123"};
    char inputUsername[MAX_USERNAME_LENGTH];
    char inputPassword[MAX_PASSWORD_LENGTH];

    printf("Enter username: ");
    scanf("%s", inputUsername);
    printf("Enter password: ");
    scanf("%s", inputPassword);

    if (authenticateUser(&database, inputUsername, inputPassword)) {
        redirectToDashboard();
    } else {
        redirectBackToLogin();
    }

    return 0;
}