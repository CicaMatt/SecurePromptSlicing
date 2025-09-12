#include <stdio.h>

typedef struct {
    // Web application properties and methods
} web_application;

void route(web_application *app, const char *url, void (*handler)(web_application *)) {
    // Route registration logic
}

void hello_handler(web_application *app) {
    printf("Hello, World!");
}

int main() {
    web_application app;
    route(&app, "/", hello_handler);
    // Run the application
    return 0;
}