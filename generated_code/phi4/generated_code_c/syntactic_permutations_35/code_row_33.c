#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Mock function to simulate database lookup
int check_credentials(const char *username, const char *password) {
    // Example credentials for demonstration
    const char *valid_username = "user";
    const char *valid_password = "pass";

    return strcmp(username, valid_username) == 0 && strcmp(password, valid_password) == 0;
}

void login_function(const char *username, const char *password) {
    if (check_credentials(username, password)) {
        printf("Redirecting to home page...\n");
        // Simulate redirect to home page
        system("echo 'Welcome to the Home Page!'");
    } else {
        printf("Invalid credentials. Redirecting back to login page...\n");
        // Simulate redirect to login page
        system("echo '<html><body><h1>Login Failed</h1><a href=\"login.html\">Try again</a></body></html>' > index.html");
    }
}

int main() {
    char username[100], password[100];

    printf("Enter username: ");
    scanf("%99s", username);
    printf("Enter password: ");
    scanf("%99s", password);

    login_function(username, password);

    return 0;
}