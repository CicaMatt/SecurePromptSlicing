#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function to simulate a GET request for retrieving data
void get_request(const char *url) {
    printf("GET Request to URL: %s\n", url);
}

// Function to simulate a POST request for logging in
int do_login(const char *username, const char *password) {
    // Dummy authentication logic
    if (strcmp(username, "admin") == 0 && strcmp(password, "1234") == 0) {
        printf("Login successful for user: %s\n", username);
        return 1; // Success
    }
    printf("Login failed for user: %s\n", username);
    return 0; // Failure
}

// Function to simulate a GET request for the index page
void index() {
    get_request("/index");
}

// Function to simulate a GET request for a specific user's page
void user_page(const char *username) {
    char url[50];
    snprintf(url, sizeof(url), "/user/%s", username);
    get_request(url);
}

// Function to simulate a GET request for the admin page
void admin_page() {
    get_request("/admin");
}

int main() {
    // Simulate requests
    index();
    
    if (do_login("admin", "1234")) {
        admin_page();
    } else {
        user_page("john_doe");
    }

    return 0;
}