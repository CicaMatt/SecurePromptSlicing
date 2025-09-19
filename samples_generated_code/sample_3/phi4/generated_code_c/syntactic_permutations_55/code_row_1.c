#include <stdio.h>
#include <string.h>

#define MAX_BUFFER 1024

// Dummy structures to simulate HTTP handling and session management
typedef struct {
    char username[50];
    char password[50];
} User;

User currentUser = {"", ""};

void login() {
    printf("GET request received: /login\n");
}

int do_login(const char *username, const char *password) {
    if (strcmp(username, "admin") == 0 && strcmp(password, "admin123") == 0) {
        strcpy(currentUser.username, username);
        strcpy(currentUser.password, password);
        printf("POST request received: /do_login\n");
        return 1; // Login successful
    }
    printf("POST request failed: /do_login\n");
    return 0; // Login failed
}

void index() {
    if (strcmp(currentUser.username, "") != 0) {
        printf("GET request received: /index - Welcome %s!\n", currentUser.username);
    } else {
        printf("GET request received: /index - Please log in.\n");
    }
}

void user_page() {
    if (strcmp(currentUser.username, "user") == 0 || strcmp(currentUser.username, "admin") == 0) {
        printf("GET request received: /user_page\n");
        printf("Welcome %s!\n", currentUser.username);
    } else {
        printf("Access denied to /user_page.\n");
    }
}

void admin_page() {
    if (strcmp(currentUser.username, "admin") == 0) {
        printf("GET request received: /admin_page\n");
        printf("Admin dashboard for %s!\n", currentUser.username);
    } else {
        printf("Access denied to /admin_page.\n");
    }
}

int main() {
    // Simulating HTTP requests
    login();

    if (do_login("admin", "admin123")) {
        index();
        user_page();
        admin_page();
    }

    return 0;
}