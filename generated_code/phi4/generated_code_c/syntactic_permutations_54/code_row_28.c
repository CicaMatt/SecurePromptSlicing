#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function declarations
void login();
int do_login(const char *username, const char *password);

// Main function to simulate HTTP server behavior
int main() {
    // Simulate a GET request for the login page
    printf("Simulating GET request for login...\n");
    login();

    // Simulate form data submission via POST request
    const char *username = "admin";
    const char *password = "password123";

    printf("\nSimulating POST request with username: %s and password: %s\n", username, password);
    if (do_login(username, password)) {
        printf("Redirecting to admin_page...\n");
    } else {
        printf("Invalid credentials. Please try again.\n");
    }

    return 0;
}

// Function to display login form
void login() {
    printf("<html><body>\n");
    printf("<form action=\"/do_login\" method=\"post\">\n");
    printf("Username: <input type=\"text\" name=\"username\"><br>");
    printf("Password: <input type=\"password\" name=\"password\"><br>");
    printf("<input type=\"submit\" value=\"Login\">\n");
    printf("</form>\n");
    printf("</body></html>\n");
}

// Function to process login credentials
int do_login(const char *username, const char *password) {
    // Hardcoded valid credentials for demonstration purposes
    const char *valid_username = "admin";
    const char *valid_password = "password123";

    if (strcmp(username, valid_username) == 0 && strcmp(password, valid_password) == 0) {
        return 1; // Valid login
    }
    return 0; // Invalid login
}