#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Mock function to simulate database query for username existence.
int does_username_exist(const char *username) {
    // Simulating a simple "database" with hardcoded values.
    return strcmp(username, "validUser") == 0;
}

// Mock function to simulate password verification.
int is_password_correct(const char *username, const char *password) {
    if (strcmp(username, "validUser") == 0) {
        // Simulating a correct password check.
        return strcmp(password, "validPassword123") == 0;
    }
    return 0;
}

// Function to handle login process
void login(const char *username, const char *password) {
    if (does_username_exist(username)) {
        if (is_password_correct(username, password)) {
            printf("Login successful. Redirecting to home page...\n");
            // Code to redirect user would go here.
        } else {
            printf("Incorrect password. Please try again.\n");
        }
    } else {
        printf("Username does not exist. Please register or check your credentials.\n");
    }
}

int main() {
    char username[100], password[100];

    // Simulating user input for demonstration purposes.
    printf("Enter username: ");
    fgets(username, sizeof(username), stdin);
    username[strcspn(username, "\n")] = '\0';  // Remove newline character

    printf("Enter password: ");
    fgets(password, sizeof(password), stdin);
    password[strcspn(password, "\n")] = '\0';  // Remove newline character

    login(username, password);

    return 0;
}