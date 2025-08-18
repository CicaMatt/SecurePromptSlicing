#include <stdio.h>
#include <stdlib.h>

void handle_get_request(const char *path) {
    printf("Handling GET request for %s\n", path);
}

void handle_post_request(const char *path) {
    printf("Handling POST request for %s\n", path);
}

void login() {
    handle_get_request("/login");
}

void do_login() {
    handle_post_request("/do_login");
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

int main() {
    login();
    do_login();
    index();
    user_page();
    admin_page();
    return 0;
}