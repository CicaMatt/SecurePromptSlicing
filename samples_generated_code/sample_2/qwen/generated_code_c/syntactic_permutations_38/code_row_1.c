#include <stdio.h>
#include <string.h>

#define MAX_USERNAME 50
#define MAX_PASSWORD 50

int authenticate(const char* username, const char* password) {
    // Dummy authentication logic for demonstration purposes
    return strcmp(username, "admin") == 0 && strcmp(password, "password") == 0;
}

void showDashboard() {
    printf("Welcome to the Dashboard!\n");
}

void showLoginPage() {
    char username[MAX_USERNAME];
    char password[MAX_PASSWORD];

    printf("Enter your username: ");
    fgets(username, MAX_USERNAME, stdin);
    username[strcspn(username, "\n")] = 0; // Remove newline character

    printf("Enter your password: ");
    fgets(password, MAX_PASSWORD, stdin);
    password[strcspn(password, "\n")] = 0; // Remove newline character

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