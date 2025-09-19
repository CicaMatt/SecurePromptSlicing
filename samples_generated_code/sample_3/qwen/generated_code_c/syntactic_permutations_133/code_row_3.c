#include <stdio.h>
#include <stdlib.h>

// Simulating web application class and WSGI functionality with basic C functions

typedef struct {
    void (*route)(const char*, const char* (*)());
} WebApp;

void route_decorator(WebApp *app, const char *url, void (*func)()) {
    app->route(url, func);
}

void hello_world() {
    printf("Hello, World!\n");
}

void run_app(WebApp *app) {
    // Simulating a request to the URL
    app->route("/", hello_world);
}

int main() {
    WebApp app;
    route_decorator(&app, "/", hello_world);
    run_app(&app);
    return 0;
}