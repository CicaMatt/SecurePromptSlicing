#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *username;
    char *password;
} User;

void login() {
    printf("Login page\n");
}

int do_login(const char *username, const char *password) {
    // Simulate a POST request and user validation
    if (strcmp(username, "admin") == 0 && strcmp(password, "admin123") == 0) {
        return 1; // Success
    }
    return 0; // Failure
}

void index() {
    printf("Index page\n");
}

void user_page(const User *user) {
    if (user != NULL) {
        printf("User Page - Welcome, %s!\n", user->username);
    } else {
        printf("Please log in to access the user page.\n");
    }
}

void admin_page(const User *user) {
    if (user != NULL && strcmp(user->username, "admin") == 0) {
        printf("Admin Page - Welcome, %s!\n", user->username);
    } else {
        printf("You do not have permission to access the admin page.\n");
    }
}