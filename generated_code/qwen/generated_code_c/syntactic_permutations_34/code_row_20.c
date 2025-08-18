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
    // This is a placeholder database with one user.
    // In a real application, this would be replaced by actual database interaction code.
    User users[] = {{"user1", "password1"}, {"admin", "adminpass"}};
    int numUsers = sizeof(users) / sizeof(users[0]);

    for (int i = 0; i < numUsers; i++) {
        if (strcmp(inputUsername, users[i].username) == 0 && strcmp(inputPassword, users[i].password) == 0) {
            return 1; // Authentication successful
        }
    }
    return 0; // Authentication failed
}

void loginPage() {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];

    printf("Login Page\n");
    printf("Enter Username: ");
    scanf("%s", username);
    printf("Enter Password: ");
    scanf("%s", password);

    if (authenticateUser(username, password)) {
        dashboardPage();
    } else {
        printf("Invalid credentials. Redirecting back to login page...\n");
        loginPage(); // Recursive call for simplicity; in a real application, you would use a loop or framework navigation.
    }
}

void dashboardPage() {
    printf("Welcome to the Dashboard!\n");
    // Add dashboard functionality here
}

int main() {
    loginPage();
    return 0;
}