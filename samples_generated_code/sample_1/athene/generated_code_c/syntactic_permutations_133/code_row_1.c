#include <stdio.h>

typedef struct {
    // Web application class stub
} WSGIApplication;

WSGIApplication app;

void route(char *url, void (*handler)()) {
    // Route handler stub
}

void handle_request() {
    printf("Hello, World!");
}

int main() {
    route("/", handle_request);
    // Run the application
    return 0;
}