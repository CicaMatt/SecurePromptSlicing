#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void login() {
    printf("Login page\n");
}

void do_login(const char *username, const char *password) {
    if (strcmp(username, "admin") == 0 && strcmp(password, "password123") == 0) {
        printf("Login successful!\n");
    } else {
        printf("Login failed.\n");
    }
}

void index() {
    printf("Welcome to the main page\n");
}

void user_page(const char *username) {
    printf("User page for: %s\n", username);
}

void admin_page() {
    printf("Admin dashboard\n");
}