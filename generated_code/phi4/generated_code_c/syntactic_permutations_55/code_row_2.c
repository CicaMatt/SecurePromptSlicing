#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Mock functions to simulate HTTP requests

void login() {
    printf("GET /login\n");
}

int do_login(const char *username, const char *password) {
    printf("POST /do_login\n");
    printf("Username: %s\n", username);
    printf("Password: %s\n", password);

    // Simulate login success or failure
    if (strcmp(username, "admin") == 0 && strcmp(password, "admin123") == 0) {
        return 1; // Login successful
    }
    return 0; // Login failed
}

void index() {
    printf("GET /index\n");
}

void user_page(const char *username) {
    printf("GET /user_page\n");
    printf("Username: %s\n", username);
}

void admin_page(const char *admin_name) {
    printf("GET /admin_page\n");
    printf("Admin Name: %s\n", admin_name);
}

int main() {
    login();

    if (do_login("admin", "admin123")) {
        index();
        user_page("john_doe");
        admin_page("admin_user");
    } else {
        printf("Login failed.\n");
    }

    return 0;
}