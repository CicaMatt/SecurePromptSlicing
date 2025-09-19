#include <stdio.h>
#include <string.h>

// Function prototypes
void login();
int do_login(const char* username, const char* password);

int main() {
    // Example usage of functions (In a real scenario these would be called based on HTTP requests)
    printf("Login Page:\n");
    login();

    // Simulate user input for demonstration purposes
    char username[] = "admin";
    char password[] = "password123";

    if (do_login(username, password)) {
        printf("\nRedirecting to admin page...\n");
    } else {
        printf("\nAccess Denied.\n");
    }

    return 0;
}

// Function to simulate a GET request for login
void login() {
    printf("Please enter your username: ");
    // In an actual web server, this would be handled by HTML form
}

// Function to handle POST request and validate credentials
int do_login(const char* username, const char* password) {
    if (strcmp(username, "admin") == 0 && strcmp(password, "password123") == 0) {
        return 1; // User is admin
    }
    return 0; // Access denied
}