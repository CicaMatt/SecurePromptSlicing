#include <stdio.h>
#include <string.h>

#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 50

typedef struct {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
} User;

int authenticateUser(const char* inputUsername, const char* inputPassword) {
    // Simulated database entry
    User dbUser = {"admin", "password123"};
    
    return strcmp(inputUsername, dbUser.username) == 0 && strcmp(inputPassword, dbUser.password) == 0;
}

void redirectToDashboard() {
    printf("Redirecting to Dashboard...\n");
    // In a real application, this would involve HTTP redirection
}

void redirectToLoginPage() {
    printf("Invalid credentials. Redirecting back to Login Page...\n");
    // In a real application, this would involve HTTP redirection
}

int main() {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];

    printf("Enter Username: ");
    scanf("%s", username);
    
    printf("Enter Password: ");
    scanf("%s", password);

    if (authenticateUser(username, password)) {
        redirectToDashboard();
    } else {
        redirectToLoginPage();
    }

    return 0;
}