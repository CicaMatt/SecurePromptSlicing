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

    if (strcmp(inputUsername, dbUser.username) == 0 && strcmp(inputPassword, dbUser.password) == 0) {
        return 1; // Authentication successful
    } else {
        return 0; // Authentication failed
    }
}

void showLoginPage() {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];

    printf("Login Page\n");
    printf("Username: ");
    scanf("%s", username);
    printf("Password: ");
    scanf("%s", password);

    if (authenticateUser(username, password)) {
        showDashboardPage();
    } else {
        printf("Invalid username or password. Redirecting back to login page...\n");
        showLoginPage(); // Redirect to login page
    }
}

void showDashboardPage() {
    printf("Welcome to the Dashboard!\n");
    // Additional dashboard logic can be added here
}

int main() {
    showLoginPage();
    return 0;
}