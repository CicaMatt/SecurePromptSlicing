#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Simulating HTTP requests and responses

void login() {
    printf("GET /login\n");
}

void do_login(const char *username, const char *password) {
    printf("POST /do_login\n");
    printf("Username: %s\n", username);
    printf("Password: %s\n", password);
}

void index() {
    printf("GET /\n");
}

void user_page() {
    printf("GET /user_page\n");
}

void admin_page() {
    printf("GET /admin_page\n");
}

int main() {
    login();
    do_login("test_user", "password123");
    index();
    user_page();
    admin_page();

    return 0;
}