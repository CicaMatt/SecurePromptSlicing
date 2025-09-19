#include <stdio.h>

typedef struct {
    // Placeholder for WSGI application structure
} web_application;

web_application app;

#define route(url, func) void func()

route("/", index) {
    printf("Hello, World!");
}

int main() {
    // Simulate running the application
    index();
    return 0;
}