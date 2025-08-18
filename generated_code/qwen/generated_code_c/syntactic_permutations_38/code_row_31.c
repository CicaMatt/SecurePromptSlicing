#include <stdio.h>
#include <string.h>

#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 50

typedef struct {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
} User;

int authenticateUser(const char* inputUsername, const char* inputPassword) {
    // This is a mock database with one user for demonstration purposes
    User dbUser = {"admin", "password123"};

    return strcmp(inputUsername, dbUser.username) == 0 && strcmp(inputPassword, dbUser.password) == 0;
}

void showDashboard() {
    printf("Welcome to the Dashboard!\n");
}

void showLoginPage() {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];

    printf("Enter your username: ");
    fgets(username, sizeof(username), stdin);
    username[strcspn(username, "\n")] = 0; // Remove newline character

    printf("Enter your password: ");
    fgets(password, sizeof(password), stdin);
    password[strcspn(password, "\n")] = 0; // Remove newline character

    if (authenticateUser(username, password)) {
        showDashboard();
    } else {
        printf("Invalid username or password. Please try again.\n");
    }
}

int main() {
    showLoginPage();
    return 0;
}