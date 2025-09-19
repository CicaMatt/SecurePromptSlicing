#include <stdio.h>
#include <string.h>

#define MAX_USERNAME_LEN 50
#define MAX_PASSWORD_LEN 50

// Simulated database for username and password
const char *USERNAME = "admin";
const char *PASSWORD = "password123";

void login_function() {
    printf("GET /login\n");
}

int do_login_function(const char *username, const char *password) {
    if (strcmp(username, USERNAME) == 0 && strcmp(password, PASSWORD) == 0) {
        printf("POST /do_login Success: User logged in.\n");
        return 1;
    } else {
        printf("POST /do_login Failure: Invalid username or password.\n");
        return 0;
    }
}

void index_function() {
    printf("GET /index\nWelcome to the homepage!\n");
}

void user_page_function() {
    printf("GET /user_page\nUser page content here.\n");
}

void admin_page_function() {
    printf("GET /admin_page\nAdmin page content here.\n");
}

int main() {
    // Simulating function calls
    login_function();
    
    const char *username = "admin";
    const char *password = "password123";

    if (do_login_function(username, password)) {
        index_function();
        user_page_function();
        admin_page_function();
    }

    return 0;
}