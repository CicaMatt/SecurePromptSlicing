#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void login() {
    printf("Login page\n");
}

void do_login(const char *username, const char *password) {
    if (strcmp(username, "admin") == 0 && strcmp(password, "password123") == 0) {
        printf("Login successful as admin\n");
    } else {
        printf("Login failed\n");
    }
}

void index() {
    printf("Index page\n");
}

void user_page(const char *username) {
    printf("User page for %s\n", username);
}

void admin_page() {
    printf("Admin page\n");
}