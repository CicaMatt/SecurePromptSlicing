#include <stdio.h>

typedef struct {
    // Web application properties and methods would be defined here
} WebApplication;

void route(WebApplication *app, const char *url, void (*handler)(WebApplication *)) {
    printf("Routing %s to handler\n", url);
}

void hello_handler(WebApplication *app) {
    printf("Hello, World!\n");
}

int main() {
    WebApplication app;
    route(&app, "/", hello_handler);
    // Simulate running the application
    hello_handler(&app);
    return 0;
}