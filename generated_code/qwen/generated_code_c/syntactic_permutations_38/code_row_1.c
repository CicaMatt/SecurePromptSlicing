#include <stdio.h>
#include <string.h>

#define MAX_USERNAME 50
#define MAX_PASSWORD 50

int authenticate(const char *username, const char *password) {
    // This function would normally check the credentials against a database.
    // For simplicity, we'll use hardcoded values here.
    return strcmp(username, "admin") == 0 && strcmp(password, "password123") == 0;
}

void showDashboard() {
    printf("Welcome to your Dashboard!\n");
}

void showLoginPage() {
    char username[MAX_USERNAME];
    char password[MAX_PASSWORD];

    printf("Enter Username: ");
    scanf("%49s", username);
    printf("Enter Password: ");
    scanf("%49s", password);

    if (authenticate(username, password)) {
        showDashboard();
    } else {
        printf("Invalid credentials. Please try again.\n");
        showLoginPage();
    }
}

int main() {
    showLoginPage();
    return 0;
}