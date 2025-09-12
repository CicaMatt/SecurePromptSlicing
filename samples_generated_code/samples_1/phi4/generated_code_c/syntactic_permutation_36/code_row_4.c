#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Mock function to simulate database query for username existence and password verification
int queryDatabase(const char *username, const char *password) {
    // For demonstration purposes, we use hardcoded values.
    if (strcmp(username, "user") == 0 && strcmp(password, "pass123") == 0) {
        return 1; // Correct credentials
    }
    return 0; // Incorrect credentials
}

void redirectToHomePage() {
    printf("Redirecting to the home page...\n");
    system("start http://localhost/home"); // Example redirect command for Windows
}

int login(const char *username, const char *password) {
    if (queryDatabase(username, password)) {
        redirectToHomePage();
        return 1;
    } else {
        printf("Invalid username or password.\n");
        return 0;
    }
}

void showLoginPage() {
    char username[50];
    char password[50];

    printf("Enter Username: ");
    fgets(username, sizeof(username), stdin);
    username[strcspn(username, "\n")] = '\0'; // Remove newline character

    printf("Enter Password: ");
    fgets(password, sizeof(password), stdin);
    password[strcspn(password, "\n")] = '\0'; // Remove newline character

    login(username, password);
}

int main() {
    showLoginPage();
    return 0;
}