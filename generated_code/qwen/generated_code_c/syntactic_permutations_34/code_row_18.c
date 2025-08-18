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
    // This is a simple representation of a database with one user
    User storedUser = {"admin", "password123"};

    return strcmp(inputUsername, storedUser.username) == 0 && strcmp(inputPassword, storedUser.password) == 0;
}

void loginPage() {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];

    printf("Enter Username: ");
    fgets(username, MAX_USERNAME_LENGTH, stdin);
    // Remove newline character from input
    username[strcspn(username, "\n")] = '\0';

    printf("Enter Password: ");
    fgets(password, MAX_PASSWORD_LENGTH, stdin);
    // Remove newline character from input
    password[strcspn(password, "\n")] = '\0';

    if (authenticateUser(username, password)) {
        printf("Login successful. Redirecting to dashboard...\n");
        dashboardPage();
    } else {
        printf("Invalid username or password. Redirecting back to login page...\n");
        loginPage();
    }
}

void dashboardPage() {
    printf("Welcome to the Dashboard!\n");
}

int main() {
    printf("Welcome to the Login Page\n");
    loginPage();

    return 0;
}