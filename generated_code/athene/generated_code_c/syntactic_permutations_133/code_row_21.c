#include <stdio.h>

typedef struct {
    // Web application structure
} WSGIApplication;

WSGIApplication app;

#define route(url, handler) void handle_request_##handler() { printf("Handling request for %s\n", url); }
route("/", index)

void index() {
    printf("Hello, World!\n");
}

int main() {
    printf("Running application...\n");
    // Simulate running the WSGI application
    handle_request_index();
    return 0;
}