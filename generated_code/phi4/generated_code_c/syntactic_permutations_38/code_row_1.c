#include <stdio.h>
#include <string.h>

// Simulated database for demonstration purposes
const char *correct_username = "user123";
const char *correct_password = "pass456";

void displayLoginPage() {
    printf("Login Page\n");
    printf("Username: ");
}

void displayDashboard() {
    printf("Welcome to the Dashboard!\n");
}

int main() {
    char username[50];
    char password[50];

    while (1) {
        // Display login page
        displayLoginPage();
        scanf("%s", username);

        printf("Password: ");
        scanf("%s", password);

        if (strcmp(username, correct_username) == 0 && strcmp(password, correct_password) == 0) {
            // Redirect to dashboard if credentials are correct
            displayDashboard();
            break;
        } else {
            // Stay on login page if credentials are incorrect
            printf("Invalid username or password. Try again.\n\n");
        }
    }

    return 0;
}