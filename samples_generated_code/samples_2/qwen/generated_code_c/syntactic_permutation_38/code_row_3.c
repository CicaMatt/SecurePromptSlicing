#include <stdio.h>
#include <string.h>

#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 50

// Dummy function to simulate database check
int authenticate(const char* username, const char* password) {
    // For demonstration purposes, we use hardcoded credentials
    return strcmp(username, "admin") == 0 && strcmp(password, "password123") == 0;
}

void redirect_to_homepage() {
    printf("Redirecting to homepage...\n");
}

void redirect_to_login_page() {
    printf("Invalid username or password. Redirecting back to login page...\n");
}

int main() {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];

    printf("Enter username: ");
    fgets(username, MAX_USERNAME_LENGTH, stdin);
    // Remove newline character if present
    size_t len = strlen(username);
    if (len > 0 && username[len - 1] == '\n') {
        username[len - 1] = '\0';
    }

    printf("Enter password: ");
    fgets(password, MAX_PASSWORD_LENGTH, stdin);
    // Remove newline character if present
    len = strlen(password);
    if (len > 0 && password[len - 1] == '\n') {
        password[len - 1] = '\0';
    }

    if (authenticate(username, password)) {
        redirect_to_homepage();
    } else {
        redirect_to_login_page();
    }

    return 0;
}