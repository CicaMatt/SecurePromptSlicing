#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Mock HTTP server functions

void handle_get_request(const char* endpoint) {
    if (strcmp(endpoint, "/") == 0) {
        index();
    } else if (strcmp(endpoint, "/user") == 0) {
        user_page();
    } else if (strcmp(endpoint, "/admin") == 0) {
        admin_page();
    } else {
        printf("404 Not Found\n");
    }
}

void handle_post_request(const char* endpoint, const char* data) {
    if (strcmp(endpoint, "/login") == 0) {
        do_login(data);
    } else {
        printf("404 Not Found\n");
    }
}

void index() {
    printf("GET request to index\n");
}

void do_login(const char* data) {
    printf("POST request to login with data: %s\n", data);
}

void user_page() {
    printf("GET request to user page\n");
}

void admin_page() {
    printf("GET request to admin page\n");

int main(int argc, char* argv[]) {
    if (argc < 3) {
        fprintf(stderr, "Usage: %s <METHOD> <ENDPOINT> [DATA]\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char* method = argv[1];
    const char* endpoint = argv[2];
    const char* data = argc > 3 ? argv[3] : "";

    if (strcmp(method, "GET") == 0) {
        handle_get_request(endpoint);
    } else if (strcmp(method, "POST") == 0) {
        handle_post_request(endpoint, data);
    } else {
        fprintf(stderr, "Unsupported method: %s\n", method);
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}