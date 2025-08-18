#include <stdio.h>
#include <stdlib.h>

typedef struct WebApplication {
    void (*route)(const char*, void(*)());
    void (*run)();
} WebApplication;

void handle_root() {
    printf("HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\nHello, World!\n");
}

void route(WebApplication *app, const char* url, void(*handler)()) {
    // In a real application, you would map URLs to handlers here
    if (strcmp(url, "/") == 0) {
        handler();
    }
}

void run(WebApplication *app) {
    // Simulate running the application and handling a request to "/"
    route(app, "/", handle_root);
}

int main() {
    WebApplication app;
    app.route = route;
    app.run = run;

    // Decorator equivalent in C: Map URL to function
    app.route(&app, "/", handle_root);

    // Run the application
    app.run(&app);

    return 0;
}