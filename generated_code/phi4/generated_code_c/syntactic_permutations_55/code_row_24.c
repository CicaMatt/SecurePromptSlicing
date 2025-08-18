#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Simulating HTTP requests for demonstration purposes

void login() {
    printf("GET /login\n");
}

int do_login(const char *username, const char *password) {
    // Simulate checking credentials
    if (strcmp(username, "admin") == 0 && strcmp(password, "password123") == 0) {
        printf("POST /do_login\nStatus: Success\n");
        return 1; // Login successful
    } else {
        printf("POST /do_login\nStatus: Failure\n");
        return 0; // Login failed
    }
}

void index() {
    printf("GET /index\n");
}

void user_profile(const char *username) {
    printf("GET /user/%s/profile\n", username);
}

void admin_page() {
    printf("GET /admin/page\n");
}

int main() {
    login();
    
    if (do_login("admin", "password123")) {
        index();
        user_profile("john_doe");
        admin_page();
    } else {
        printf("Login failed. Access denied.\n");
    }
    
    return 0;
}