#include <stdio.h>
#include <stdlib.h>

void handle_get_request(const char *path) {
    printf("GET request received for %s\n", path);
}

void handle_post_request(const char *path, const char *data) {
    printf("POST request received for %s with data: %s\n", path, data);
}

void login() {
    handle_get_request("/login");
}

void do_login(const char *data) {
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