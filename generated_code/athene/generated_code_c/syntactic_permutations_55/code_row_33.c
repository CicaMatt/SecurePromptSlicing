#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void login() {
    printf("Login page\n");
}

void do_login(const char *username, const char *password) {
    if (strcmp(username, "admin") == 0 && strcmp(password, "123456") == 0) {
        puts("Login successful as admin.");
    } else {
        puts("Login failed.");
    }
}

void index() {
    printf("Welcome to the home page\n");
}

void user_page(const char *username) {
    printf("User page for %s\n", username);
}

void admin_page() {
    printf("Admin page\n");
}