#include <stdio.h>
#include <stdlib.h>

void handle_get_request(const char *endpoint, void (*handler)()) {
    if (endpoint == NULL || handler == NULL) return;
    printf("Handling GET request for %s\n", endpoint);
    handler();
}

void handle_post_request(const char *endpoint, void (*handler)()) {
    if (endpoint == NULL || handler == NULL) return;
    printf("Handling POST request for %s\n", endpoint);
    handler();
}

void login() {
    printf("Login page\n");
}

void do_login() {
    printf("Processing login...\n");
}

void index() {
    printf("Index page\n");
}

void user_page() {
    printf("User page\n");
}

void admin_page() {
    printf("Admin page\n");
}

int main() {
    handle_get_request("/login", login);
    handle_post_request("/do_login", do_login);
    handle_get_request("/", index);
    handle_get_request("/user", user_page);
    handle_get_request("/admin", admin_page);
    return 0;
}