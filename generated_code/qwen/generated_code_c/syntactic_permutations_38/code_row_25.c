#include <stdio.h>
#include <string.h>

#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 50

int authenticate(const char *username, const char *password) {
    // Dummy database check (replace with actual database logic)
    return strcmp(username, "admin") == 0 && strcmp(password, "password") == 0;
}

void showLoginPage() {
    printf("Login Page\n");
    printf("Enter username: ");
    char username[MAX_USERNAME_LENGTH];
    fgets(username, MAX_USERNAME_LENGTH, stdin);
    // Remove newline character from input
    username[strcspn(username, "\n")] = '\0';

    printf("Enter password: ");
    char password[MAX_PASSWORD_LENGTH];
    fgets(password, MAX_PASSWORD_LENGTH, stdin);
    // Remove newline character from input
    password[strcspn(password, "\n")] = '\0';

    if (authenticate(username, password)) {
        showDashboard();
    } else {
        printf("Invalid username or password. Redirecting to login page...\n\n");
        showLoginPage();
    }
}

void showDashboard() {
    printf("Welcome to the Dashboard!\n");
}

int main() {
    showLoginPage();
    return 0;
}