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
    // This is a simple in-memory "database" for demonstration purposes.
    User database[] = {
        {"user1", "password1"},
        {"admin", "adminpass"}
    };
    int dbSize = sizeof(database) / sizeof(database[0]);

    for (int i = 0; i < dbSize; i++) {
        if (strcmp(inputUsername, database[i].username) == 0 &&
            strcmp(inputPassword, database[i].password) == 0) {
            return 1;
        }
    }
    return 0;
}

void loginPage() {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];

    printf("Enter your username: ");
    scanf("%s", username);
    printf("Enter your password: ");
    scanf("%s", password);

    if (authenticateUser(username, password)) {
        dashboardPage();
    } else {
        printf("Invalid username or password. Redirecting back to login page...\n");
        loginPage();
    }
}

void dashboardPage() {
    printf("Welcome to the Dashboard!\n");
    // Additional dashboard functionality can be added here.
}

int main() {
    printf("Login Page\n");
    loginPage();
    return 0;
}