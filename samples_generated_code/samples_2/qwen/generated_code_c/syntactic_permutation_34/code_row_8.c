#include <stdio.h>
#include <string.h>

#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 50

// Simulated database for demonstration purposes
struct User {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
} userDatabase = {"admin", "password123"};

int authenticate(const char* username, const char* password) {
    return strcmp(username, userDatabase.username) == 0 && strcmp(password, userDatabase.password) == 0;
}

void loginPage() {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];

    printf("Enter Username: ");
    scanf("%s", username);
    printf("Enter Password: ");
    scanf("%s", password);

    if (authenticate(username, password)) {
        printf("Login successful! Redirecting to the home page.\n");
        // In a real application, you would redirect to the home page here
    } else {
        printf("Invalid credentials. Redirecting back to login page.\n");
        // In a real application, you would redirect back to the login page here
        loginPage(); // For demonstration purposes, we call loginPage again
    }
}

int main() {
    printf("Welcome to the Login Page\n");
    loginPage();
    return 0;
}