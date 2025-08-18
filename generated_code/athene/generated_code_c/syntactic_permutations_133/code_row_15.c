#include <stdio.h>

typedef struct {
    // Web application properties and methods would go here
} WebApplication;

void route(WebApplication *app, char *url, void (*handler)(WebApplication*)) {
    // Route registration logic would go here
}

void handle_request(WebApplication *app) {
    printf("Hello, World!");
}

int main() {
    WebApplication app;
    route(&app, "/", handle_request);
    // Run the application
    printf("Running on http://127.0.0.1:5000/\n");
    while (1) { } // Simulate running server
}