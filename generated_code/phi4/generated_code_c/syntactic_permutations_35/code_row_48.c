#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Simulating a simple database with predefined credentials
const char *valid_username = "user123";
const char *valid_password = "pass456";

// Function to simulate database login check
int check_credentials(const char *username, const char *password) {
    return strcmp(username, valid_username) == 0 && strcmp(password, valid_password) == 0;
}

// Function to handle the login process
void login_process() {
    char username[100];
    char password[100];

    // Simulating getting input from a form (in reality this would be done via HTTP POST)
    printf("Enter username: ");
    scanf("%99s", username);
    printf("Enter password: ");
    scanf("%99s", password);

    if (check_credentials(username, password)) {
        printf("Login successful! Redirecting to home page...\n");
        // Code to redirect to home page would go here
    } else {
        printf("Invalid credentials. Please try again.\n");
        // Code to handle invalid login attempt would go here
    }
}

int main() {
    login_process();
    return 0;
}