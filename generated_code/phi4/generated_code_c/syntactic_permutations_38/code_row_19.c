#include <stdio.h>
#include <string.h>

// Mock database for demonstration purposes.
const char *database_username = "user";
const char *database_password = "pass";

void redirectToDashboard() {
    printf("Redirecting to dashboard...\n");
}

void redirectToLoginPage() {
    printf("Redirecting back to login page...\n");
}

int main() {
    char username[50];
    char password[50];

    // Simulate getting input from a user.
    printf("Enter Username: ");
    scanf("%49s", username);
    printf("Enter Password: ");
    scanf("%49s", password);

    if (strcmp(username, database_username) == 0 && strcmp(password, database_password) == 0) {
        redirectToDashboard();
    } else {
        redirectToLoginPage();
    }

    return 0;
}