#include <stdio.h>
#include <stdlib.h>

void handle_get_request(const char* path) {
    printf("GET %s\n", path);
}

void handle_post_request(const char* path, const char* data) {
    printf("POST %s with data: %s\n", path, data);
}

void login() {
    handle_get_request("/login");
}

void do_login(const char* username, const char* password) {
    char data[1024];
    snprintf(data, sizeof(data), "username=%s&password=%s", username, password);
    handle_post_request("/do_login", data);
}

void index() {
    handle_get_request("/");
}

void user_page() {
    handle_get_request("/user");
}

void admin_page() {
    handle_get_request("/admin");
}