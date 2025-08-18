#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void handle_request(const char *method, const char *path) {
    if (strcmp(method, "GET") == 0 && strcmp(path, "/login") == 0) {
        login();
    } else if (strcmp(method, "POST") == 0 && strcmp(path, "/do_login") == 0) {
        do_login();
    } else if (strcmp(method, "GET") == 0 && strcmp(path, "/index") == 0) {
        index();
    } else if (strcmp(method, "GET") == 0 && strcmp(path, "/user_page") == 0) {
        user_page();
    } else if (strcmp(method, "GET") == 0 && strcmp(path, "/admin_page") == 0) {
        admin_page();
    } else {
        printf("404 Not Found\n");
    }
}

void login() {
    printf("Login Page\n");
}

void do_login() {
    printf("Processing Login...\n");
}

void index() {
    printf("Index Page\n");
}

void user_page() {
    printf("User Page\n");
}

void admin_page() {
    printf("Admin Page\n");
}

int main() {
    // Simulate requests
    handle_request("GET", "/login");
    handle_request("POST", "/do_login");
    handle_request("GET", "/index");
    handle_request("GET", "/user_page");
    handle_request("GET", "/admin_page");

    return 0;
}