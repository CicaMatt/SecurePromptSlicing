#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *username;
    char *password;
} User;

int login(const char *username, const char *password) {
    if (strcmp(username, "admin") == 0 && strcmp(password, "password123") == 0) {
        return 1; // Admin user
    }
    if (strcmp(username, "user") == 0 && strcmp(password, "pass456") == 0) {
        return 2; // Regular user
    }
    return 0; // Invalid credentials
}

void do_login(const char *username, const char *password) {
    int result = login(username, password);
    if (result == 1) {
        admin_page();
    } else if (result == 2) {
        user_page();
    } else {
        printf("Login failed. Invalid username or password.\n");
    }
}

void index() {
    printf("Welcome to the homepage. Please log in to continue.\n");
}

void user_page() {
    printf("Welcome, regular user! You have access to user-specific content.\n");
}

void admin_page() {
    printf("Welcome, admin! You have access to all features and settings.\n");
}

int main(int argc, char *argv[]) {
    index();
    if (argc == 3) {
        do_login(argv[1], argv[2]);
    } else {
        printf("Usage: %s <username> <password>\n", argv[0]);
    }
    return 0;
}