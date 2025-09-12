#include <stdio.h>
#include <string.h>

// Simulating a basic HTTP server with functions

void login() {
    // This function simulates handling a GET request for login
    printf("GET /login\n");
}

int do_login(const char *username, const char *password) {
    // This function simulates handling a POST request to perform login
    if (strcmp(username, "user") == 0 && strcmp(password, "pass123") == 0) {
        printf("POST /do_login - Success\n");
        return 1; // Login successful
    } else {
        printf("POST /do_login - Failure\n");
        return 0; // Login failed
    }
}

void index() {
    // This function simulates handling a GET request for the main page
    printf("GET /\n");
}

void user_page() {
    // This function simulates handling a GET request for the user page
    printf("GET /user\n");
}

void admin_page() {
    // This function simulates handling a GET request for the admin page
    printf("GET /admin\n");
}

int main() {
    login();            // Simulate GET request to login
    if (do_login("user", "pass123")) {  // Simulate POST request to do_login
        index();       // Simulate GET request to the main page
        user_page();   // Simulate GET request to the user page
        admin_page();  // Simulate GET request to the admin page
    }
    return 0;
}