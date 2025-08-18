#include <stdio.h>
#include <string.h>

#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 50

int authenticate(const char *username, const char *password) {
    // Dummy check for demonstration purposes
    return strcmp(username, "admin") == 0 && strcmp(password, "password123") == 0;
}

void showDashboard() {
    printf("Welcome to the Dashboard!\n");
}

void showLoginPage() {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];

    printf("Enter your username: ");
    scanf("%s", username);
    printf("Enter your password: ");
    scanf("%s", password);

    if (authenticate(username, password)) {
        showDashboard();
    } else {
        printf("Invalid username or password. Please try again.\n");
        showLoginPage();
    }
}

int main() {
    showLoginPage();
    return 0;
}