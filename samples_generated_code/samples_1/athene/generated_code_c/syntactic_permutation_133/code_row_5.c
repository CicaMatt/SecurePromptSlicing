#include <stdio.h>

typedef struct {
    // Web application class properties and methods would be defined here
} web_application;

void decorator(web_application *app, char *url, void (*func)(web_application *)) {
    // Decorator to map URL to function
}

void hello_world(web_application *app) {
    printf("Hello, World!");
}

int main() {
    web_application app;
    decorator(&app, "/", hello_world);
    // Simulate running the application (in a real scenario, this would start a server)
    hello_world(&app);
    return 0;
}