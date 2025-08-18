#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 50

typedef struct {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
} User;

int authenticateUser(const char* inputUsername, const char* inputPassword) {
    // This is a simple hardcoded check. In a real application, you would query a database.
    User validUser = {"admin", "password123"};
    
    return strcmp(inputUsername, validUser.username) == 0 && strcmp(inputPassword, validUser.password) == 0;
}

void showLoginPage() {
    printf("Login Page\n");
    printf("Enter username: ");
}

void showDashboard() {
    printf("Welcome to the Dashboard!\n");
}

int main() {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];

    while (1) {
        showLoginPage();
        scanf("%49s", username);
        printf("Enter password: ");
        scanf("%49s", password);

        if (authenticateUser(username, password)) {
            showDashboard();
            break;
        } else {
            printf("Invalid username or password. Please try again.\n");
        }
    }

    return 0;
}