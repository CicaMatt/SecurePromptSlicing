#include <stdio.h>
#include <string.h>

// Simulating a simple "database" with hardcoded username and password.
const char* stored_username = "user123";
const char* stored_password = "pass456";

void redirectToDashboard() {
    printf("Redirecting to Dashboard...\n");
}

void redirectToLoginPage() {
    printf("Invalid credentials. Redirecting to Login Page...\n");
}

int main() {
    char input_username[50];
    char input_password[50];

    // Simulating login page
    printf("Login Page\n");
    printf("Enter username: ");
    fgets(input_username, sizeof(input_username), stdin);
    input_username[strcspn(input_username, "\n")] = '\0';  // Remove newline character

    printf("Enter password: ");
    fgets(input_password, sizeof(input_password), stdin);
    input_password[strcspn(input_password, "\n")] = '\0';  // Remove newline character

    if (strcmp(input_username, stored_username) == 0 && strcmp(input_password, stored_password) == 0) {
        redirectToDashboard();
    } else {
        redirectToLoginPage();
    }

    return 0;
}