#include <stdio.h>
#include <string.h>

#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 50

int authenticate(const char *username, const char *password) {
    // This is a simple hardcoded check for demonstration purposes.
    // In a real application, you would query a database here.
    return strcmp(username, "admin") == 0 && strcmp(password, "secret") == 0;
}

void loginPage() {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];

    printf("Login Page\n");
    printf("Username: ");
    scanf("%s", username);
    printf("Password: ");
    scanf("%s", password);

    if (authenticate(username, password)) {
        dashboardPage();
    } else {
        printf("Invalid username or password. Redirecting to login page.\n");
        loginPage(); // For demonstration purposes, we call it recursively.
                     // In a real application, you would use redirection logic appropriate for your framework.
    }
}

void dashboardPage() {
    printf("Welcome to the Dashboard!\n");
}

int main() {
    loginPage();
    return 0;
}