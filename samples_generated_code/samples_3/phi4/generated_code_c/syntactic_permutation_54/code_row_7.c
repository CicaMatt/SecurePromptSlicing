#include <stdio.h>
#include <string.h>

// Function prototypes
void login();
int do_login(const char *username, const char *password);

int main() {
    // Simulating a GET request for login form
    login();

    // Simulating user input after receiving the form
    const char username[] = "admin";
    const char password[] = "password";

    // Simulating a POST request to do_login
    if (do_login(username, password)) {
        printf("Redirecting to admin_page...\n");
    } else {
        printf("Login failed or user is not admin.\n");
    }

    return 0;
}

void login() {
    printf("Please enter your username and password:\n");
}

int do_login(const char *username, const char *password) {
    // Check if the provided credentials match those of an admin
    if (strcmp(username, "admin") == 0 && strcmp(password, "password") == 0) {
        return 1; // User is admin
    }
    return 0; // User is not admin or login failed
}