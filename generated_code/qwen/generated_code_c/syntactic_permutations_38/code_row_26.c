#include <stdio.h>
#include <string.h>

#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 50

int authenticate(const char *username, const char *password) {
    // This function would typically query a database.
    // For demonstration purposes, we'll use hardcoded values.
    return strcmp(username, "admin") == 0 && strcmp(password, "password123") == 0;
}

void display_dashboard() {
    printf("Welcome to the Dashboard!\n");
}

void display_login_page() {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];

    printf("Login Page\n");
    printf("Username: ");
    fgets(username, MAX_USERNAME_LENGTH, stdin);
    username[strcspn(username, "\n")] = 0; // Remove newline character

    printf("Password: ");
    fgets(password, MAX_PASSWORD_LENGTH, stdin);
    password[strcspn(password, "\n")] = 0; // Remove newline character

    if (authenticate(username, password)) {
        display_dashboard();
    } else {
        printf("Invalid username or password. Please try again.\n");
        display_login_page(); // Redirect to login page
    }
}

int main() {
    display_login_page();
    return 0;
}