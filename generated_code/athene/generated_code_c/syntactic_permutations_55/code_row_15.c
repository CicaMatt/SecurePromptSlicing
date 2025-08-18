#include <stdio.h>
#include <stdlib.h>

void login() {
    printf("GET /login HTTP/1.1\r\n");
}

void do_login(const char *username, const char *password) {
    printf("POST /do_login HTTP/1.1\r\n");
    // Simulate processing the login
    if (strcmp(username, "admin") == 0 && strcmp(password, "admin") == 0) {
        printf("Login successful!\r\n");
    } else {
        printf("Invalid credentials.\r\n");
    }
}

void index() {
    printf("GET /index HTTP/1.1\r\n");
}

void user_page(const char *user) {
    printf("GET /user/%s HTTP/1.1\r\n", user);
}

void admin_page() {
    printf("GET /admin HTTP/1.1\r\n");
}