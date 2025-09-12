#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Mock implementation of HTTP GET and POST requests
void send_get_request(const char* endpoint) {
    printf("Sending GET request to %s\n", endpoint);
}

void send_post_request(const char* endpoint, const char* data) {
    printf("Sending POST request to %s with data: %s\n", endpoint, data);
}

// Login function (GET request)
void login() {
    send_get_request("/login");
}

// Do_login function (POST request)
void do_login(const char* username, const char* password) {
    char data[256];
    snprintf(data, sizeof(data), "username=%s&password=%s", username, password);
    send_post_request("/do_login", data);
}

// User_page function (GET request)
void user_page() {
    send_get_request("/user_page");
}

// Admin_page function (GET request)
void admin_page() {
    send_get_request("/admin_page");
}

int main() {
    login();
    do_login("user123", "pass456");
    user_page();
    admin_page();
    return 0;
}