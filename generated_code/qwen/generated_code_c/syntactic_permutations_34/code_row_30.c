#include <stdio.h>
#include <string.h>

#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 50

typedef struct {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
} User;

int authenticateUser(const char* inputUsername, const char* inputPassword) {
    // This is a mock database for demonstration purposes
    User database[] = {
        {"user1", "password1"},
        {"user2", "password2"}
    };
    int numberOfUsers = sizeof(database) / sizeof(User);

    for (int i = 0; i < numberOfUsers; i++) {
        if (strcmp(inputUsername, database[i].username) == 0 && strcmp(inputPassword, database[i].password) == 0) {
            return 1; // Authentication successful
        }
    }
    return 0; // Authentication failed
}

void showLoginPage() {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];

    printf("Enter Username: ");
    scanf("%s", username);
    printf("Enter Password: ");
    scanf("%s", password);

    if (authenticateUser(username, password)) {
        printf("Login successful. Redirecting to dashboard...\n");
        showDashboardPage();
    } else {
        printf("Invalid credentials. Redirecting back to login page...\n");
        showLoginPage();
    }
}

void showDashboardPage() {
    printf("Welcome to the Dashboard!\n");
}

int main() {
    showLoginPage();
    return 0;
}