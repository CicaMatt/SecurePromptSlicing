#include <stdio.h>
#include <string.h>

#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 50

typedef struct {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
} User;

int authenticateUser(const char* enteredUsername, const char* enteredPassword) {
    // Simulated database entry
    User dbUser = {"user123", "pass456"};

    return strcmp(enteredUsername, dbUser.username) == 0 && strcmp(enteredPassword, dbUser.password) == 0;
}

void redirectToDashboard() {
    printf("Redirecting to Dashboard...\n");
}

void showLoginPage() {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];

    printf("Login Page\n");
    printf("Enter Username: ");
    scanf("%s", username);
    printf("Enter Password: ");
    scanf("%s", password);

    if (authenticateUser(username, password)) {
        redirectToDashboard();
    } else {
        printf("Invalid credentials. Redirecting back to Login Page...\n");
        showLoginPage(); // Recursive call for demonstration; in a real application, this should be handled differently
    }
}

int main() {
    showLoginPage();
    return 0;
}