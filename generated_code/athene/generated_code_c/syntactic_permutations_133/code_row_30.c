#include <stdio.h>

typedef struct {
    // Web application properties and methods would be defined here
} WebApplication;

WebApplication app;

#define route(url, handler) void handle_##handler()

route("/", index) {
    printf("Hello, World!");
}

int main() {
    // Simulate running the application
    index();
    return 0;
}