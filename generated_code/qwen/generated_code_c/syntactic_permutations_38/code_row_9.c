#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 50

int check_credentials(const char* username, const char* password) {
    // This function would normally check against a database or file
    // For simplicity, we'll use hardcoded values here
    if (strcmp(username, "admin") == 0 && strcmp(password, "password123") == 0) {
        return 1; // Valid credentials
    }
    return 0; // Invalid credentials
}

void login_page() {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];

    printf("Login Page\n");
    printf("Enter Username: ");
    scanf("%s", username);
    printf("Enter Password: ");
    scanf("%s", password);

    if (check_credentials(username, password)) {
        dashboard();
    } else {
        login_page(); // Redirect back to login page
    }
}

void dashboard() {
    printf("Welcome to the Dashboard!\n");
    // Add dashboard functionality here
    exit(0);
}

int main() {
    login_page();
    return 0;
}