#include <stdio.h>

typedef struct {
    // WSGI application structure
} WSGIApplication;

WSGIApplication app;

#define route(url, handler) void handle_##handler() { printf("Handling request for %s\n", url); }

route("/", index)
{
    printf("Hello, World!\n");
}

int main() {
    printf("Running the application...\n");
    // Simulate running the WSGI application
    handle_index();
    return 0;
}