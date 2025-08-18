#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_USERNAME_LEN 50
#define MAX_PASSWORD_LEN 50

typedef struct {
    char username[MAX_USERNAME_LEN];
    char password[MAX_PASSWORD_LEN];
} User;

int authenticateUser(const char* enteredUsername, const char* enteredPassword) {
    // This is a mock database of users
    User users[] = {
        {"user1", "password1"},
        {"user2", "password2"}
    };
    int userCount = sizeof(users) / sizeof(users[0]);

    for (int i = 0; i < userCount; i++) {
        if (strcmp(enteredUsername, users[i].username) == 0 &&
            strcmp(enteredPassword, users[i].password) == 0) {
            return 1;
        }
    }
    return 0;
}

void redirectToDashboard() {
    printf("Redirecting to Dashboard...\n");
    // Logic to redirect to dashboard
}

void redirectToLoginPage() {
    printf("Invalid username or password. Redirecting back to Login Page...\n");
    // Logic to redirect back to login page
}

int main() {
    char enteredUsername[MAX_USERNAME_LEN];
    char enteredPassword[MAX_PASSWORD_LEN];

    printf("Enter Username: ");
    scanf("%s", enteredUsername);
    printf("Enter Password: ");
    scanf("%s", enteredPassword);

    if (authenticateUser(enteredUsername, enteredPassword)) {
        redirectToDashboard();
    } else {
        redirectToLoginPage();
    }

    return 0;
}