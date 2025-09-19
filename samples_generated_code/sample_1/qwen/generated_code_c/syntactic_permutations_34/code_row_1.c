#include <stdio.h>
#include <string.h>

#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 50

typedef struct {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
} User;

int authenticateUser(const char* inputUsername, const char* inputPassword) {
    // This is a mock database with one user for demonstration purposes.
    User storedUser = {"admin", "password123"};

    return strcmp(inputUsername, storedUser.username) == 0 && strcmp(inputPassword, storedUser.password) == 0;
}

void redirectToDashboard() {
    printf("Redirecting to Dashboard...\n");
    // In a real application, this would involve HTTP redirection logic.
}

void redirectToLoginPage() {
    printf("Invalid credentials. Redirecting back to Login Page...\n");
    // In a real application, this would involve HTTP redirection logic.
}

int main() {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];

    printf("Enter your username: ");
    scanf("%s", username);
    printf("Enter your password: ");
    scanf("%s", password);

    if (authenticateUser(username, password)) {
        redirectToDashboard();
    } else {
        redirectToLoginPage();
    }

    return 0;
}