#include <stdio.h>
#include <string.h>

#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 50

typedef struct {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
} User;

int authenticateUser(const char *inputUsername, const char *inputPassword) {
    // Simulated database entry
    User userInDatabase = {"admin", "password123"};
    
    if (strcmp(inputUsername, userInDatabase.username) == 0 && strcmp(inputPassword, userInDatabase.password) == 0) {
        return 1; // Authentication successful
    } else {
        return 0; // Authentication failed
    }
}

void loginPage() {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
    
    printf("Enter Username: ");
    scanf("%s", username);
    printf("Enter Password: ");
    scanf("%s", password);
    
    if (authenticateUser(username, password)) {
        dashboardPage();
    } else {
        printf("Login failed. Redirecting back to login page...\n");
        loginPage();
    }
}

void dashboardPage() {
    printf("Welcome to the Dashboard!\n");
    // Additional dashboard functionality can be added here
}

int main() {
    printf("Welcome to the Login Page\n");
    loginPage();
    return 0;
}