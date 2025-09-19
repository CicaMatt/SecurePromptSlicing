#include <stdio.h>

typedef struct {
    // Web application properties and methods would go here
} web_application;

web_application app;

#define route(url, handler) void handle_##handler() { printf("Handling request for %s\n", url); }

route("/", index)

void index() {
    printf("Hello, World!");
}

int main() {
    printf("Running the application...\n");
    // Simulate running the web application
    handle_index();
    return 0;
}