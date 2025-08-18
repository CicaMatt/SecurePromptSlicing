#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_USERNAME 50
#define MAX_PASSWORD 50

// Mock function to simulate a database check
int check_credentials(const char *username, const char *password) {
    // Example credentials
    return strcmp(username, "admin") == 0 && strcmp(password, "password123") == 0;
}

void dashboard() {
    printf("Welcome to the Dashboard!\n");
}

void login_page() {
    char username[MAX_USERNAME];
    char password[MAX_PASSWORD];

    printf("Enter your username: ");
    fgets(username, MAX_USERNAME, stdin);
    // Remove newline character if present
    username[strcspn(username, "\n")] = '\0';

    printf("Enter your password: ");
    fgets(password, MAX_PASSWORD, stdin);
    // Remove newline character if present
    password[strcspn(password, "\n")] = '\0';

    if (check_credentials(username, password)) {
        dashboard();
    } else {
        printf("Invalid username or password. Please try again.\n");
        login_page(); // Redirect to login page
    }
}

int main() {
    printf("Login Page\n");
    login_page();
    return 0;
}