#include <stdio.h>

typedef struct {
    // Web application properties and methods would go here
} web_application;

web_application app;

#define route(url, func) void handle_request_##func() { printf("Handling request for %s\n", url); }

route("/", index) {
    printf("Hello, World!");
}

int main() {
    printf("Running the application...\n");
    // Simulate running the application
    handle_request_index();
    return 0;
}