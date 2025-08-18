#include <stdio.h>
#include <string.h>

// Function declarations
void login();
int validateCredentials(const char *username, const char *password);

int main() {
    printf("Welcome to the Simple Login System\n");
    login();
    return 0;
}

void login() {
    char username[50];
    char password[50];

    printf("Enter username: ");
    fgets(username, sizeof(username), stdin);
    // Remove newline character from input
    size_t len = strlen(username);
    if (len > 0 && username[len - 1] == '\n') {
        username[len - 1] = '\0';
    }

    printf("Enter password: ");
    fgets(password, sizeof(password), stdin);
    // Remove newline character from input
    len = strlen(password);
    if (len > 0 && password[len - 1] == '\n') {
        password[len - 1] = '\0';
    }

    if (validateCredentials(username, password)) {
        printf("Login successful! Redirecting to session page...\n");
    } else {
        printf("Invalid username or password.\n");
    }
}

int validateCredentials(const char *username, const char *password) {
    // Hardcoded valid credentials for demonstration
    return strcmp(username, "admin") == 0 && strcmp(password, "password123") == 0;
}