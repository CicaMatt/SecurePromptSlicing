#include <stdio.h>
#include <string.h>

#define MAX_USERNAME_LEN 50
#define MAX_PASSWORD_LEN 50

void showLoginPage();
int authenticateUser(const char *username, const char *password);

int main() {
    char username[MAX_USERNAME_LEN];
    char password[MAX_PASSWORD_LEN];

    showLoginPage();

    printf("Enter username: ");
    fgets(username, sizeof(username), stdin);
    username[strcspn(username, "\n")] = '\0'; // Remove newline character

    printf("Enter password: ");
    fgets(password, sizeof(password), stdin);
    password[strcspn(password, "\n")] = '\0'; // Remove newline character

    if (authenticateUser(username, password)) {
        printf("Login successful! Redirecting to session page...\n");
    } else {
        printf("Incorrect username or password. Please try again.\n");
    }

    return 0;
}

void showLoginPage() {
    printf("Welcome to the Login Page\n");
    printf("========================\n");
}

int authenticateUser(const char *username, const char *password) {
    // Hardcoded credentials for demonstration
    const char *correctUsername = "user";
    const char *correctPassword = "pass";

    return strcmp(username, correctUsername) == 0 && strcmp(password, correctPassword) == 0;
}