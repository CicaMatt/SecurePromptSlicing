#include <stdio.h>
#include <string.h>

#define MAX_USERNAME_LEN 50
#define MAX_PASSWORD_LEN 50

int authenticate(const char* username, const char* password) {
    // This function should check the provided username and password against a database.
    // For simplicity, we're using hardcoded values here.
    if (strcmp(username, "admin") == 0 && strcmp(password, "password123") == 0) {
        return 1; // Authentication successful
    }
    return 0; // Authentication failed
}

void redirect_to_dashboard() {
    printf("Redirecting to dashboard...\n");
    // In a real application, this would involve HTTP redirection.
}

void redirect_to_login() {
    printf("Invalid username or password. Redirecting back to login page...\n");
    // In a real application, this would involve HTTP redirection.
}

int main() {
    char username[MAX_USERNAME_LEN];
    char password[MAX_PASSWORD_LEN];

    printf("Enter your username: ");
    fgets(username, sizeof(username), stdin);
    username[strcspn(username, "\n")] = '\0'; // Remove newline character

    printf("Enter your password: ");
    fgets(password, sizeof(password), stdin);
    password[strcspn(password, "\n")] = '\0'; // Remove newline character

    if (authenticate(username, password)) {
        redirect_to_dashboard();
    } else {
        redirect_to_login();
    }

    return 0;
}