#include <stdio.h>
#include <string.h>

#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 50

typedef struct {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
} User;

int authenticateUser(const char* inputUsername, const char* inputPassword) {
    // This is a simple hardcoded database simulation for demonstration purposes.
    // In a real application, you would query a database here.
    User dbUser = {"admin", "password123"};

    return strcmp(inputUsername, dbUser.username) == 0 && strcmp(inputPassword, dbUser.password) == 0;
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
        // In a web application, you would redirect the user to the dashboard page here.
    } else {
        printf("Invalid username or password. Redirecting back to login page...\n");
        showLoginPage(); // Redirect back to the login page
    }
}

int main() {
    showLoginPage();
    return 0;
}