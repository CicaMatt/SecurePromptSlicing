#include <stdio.h>
#include <string.h>

#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 50

int authenticate(const char* username, const char* password) {
    // Dummy database for demonstration purposes
    const char* storedUsername = "admin";
    const char* storedPassword = "password";

    return strcmp(username, storedUsername) == 0 && strcmp(password, storedPassword) == 0;
}

void showLoginPage() {
    printf("Login Page\n");
    printf("Enter Username: ");
}

void showDashboardPage() {
    printf("Welcome to the Dashboard!\n");
}

int main() {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];

    while (1) {
        showLoginPage();
        scanf("%s", username);

        printf("Enter Password: ");
        scanf("%s", password);

        if (authenticate(username, password)) {
            showDashboardPage();
            break;
        } else {
            printf("Invalid credentials. Please try again.\n");
        }
    }

    return 0;
}