#include <stdio.h>

typedef struct {
    // Web application properties and methods would go here
} web_application;

web_application app;

#define route(url, handler) void handle_##handler() { printf("Handling %s\n", url); }

route("/", index)
{
    printf("Hello, World!");
}

int main() {
    printf("Running server...\n");
    // Simulate running the application (in a real scenario this would start an HTTP server)
    handle_index();
    return 0;
}