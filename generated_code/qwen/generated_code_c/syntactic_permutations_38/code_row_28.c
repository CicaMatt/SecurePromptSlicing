#include <stdio.h>
#include <string.h>

#define MAX_USERNAME 50
#define MAX_PASSWORD 50

int authenticate(const char *username, const char *password) {
    // Dummy check for demonstration purposes
    return strcmp(username, "admin") == 0 && strcmp(password, "password123") == 0;
}

void showLoginPage() {
    printf("Login Page\n");
    printf("Enter username: ");
}

void showDashboard() {
    printf("Welcome to the Dashboard!\n");
}

int main() {
    char username[MAX_USERNAME];
    char password[MAX_PASSWORD];

    while (1) {
        showLoginPage();
        scanf("%s", username);
        printf("Enter password: ");
        scanf("%s", password);

        if (authenticate(username, password)) {
            showDashboard();
            break;
        } else {
            printf("Invalid username or password. Please try again.\n");
        }
    }

    return 0;
}