#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void handle_get_request(const char *path) {
    printf("GET request for %s\n", path);
}

void handle_post_request(const char *path) {
    printf("POST request for %s\n", path);
}

void login() {
    handle_get_request("/login");
}

void submit_login() {
    handle_post_request("/submit_login");
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