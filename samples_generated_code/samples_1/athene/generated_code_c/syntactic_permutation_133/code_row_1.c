#include <stdio.h>

typedef struct {
    // Web application properties and methods would be defined here
} WSGIApplication;

WSGIApplication app;

#define route(url, handler) void handle_##handler()

route("/", index) {
    printf("Hello, World!");
}

int main() {
    // Run the application
    return 0;
}