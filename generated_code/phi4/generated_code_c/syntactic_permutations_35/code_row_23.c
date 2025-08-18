#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Mock function to simulate checking credentials against a "database"
int check_credentials(const char *username, const char *password) {
    // Simulated database entries
    const char valid_username[] = "user123";
    const char valid_password[] = "pass456";

    return (strcmp(username, valid_username) == 0 && strcmp(password, valid_password) == 0);
}

void login() {
    char username[100];
    char password[100];

    printf("Enter username: ");
    fgets(username, sizeof(username), stdin);
    username[strcspn(username, "\n")] = '\0'; // Remove newline character

    printf("Enter password: ");
    fgets(password, sizeof(password), stdin);
    password[strcspn(password, "\n")] = '\0'; // Remove newline character

    if (check_credentials(username, password)) {
        printf("Redirecting to home page...\n");
        system("echo 'Access Granted. Welcome to the Home Page!'"); // Simulate redirection
    } else {
        printf("Invalid credentials. Redirecting to login page...\n");
        system("echo 'Please try again.'"); // Simulate redirection back to login
    }
}

int main() {
    printf("Login Page\n");
    login();
    return 0;
}