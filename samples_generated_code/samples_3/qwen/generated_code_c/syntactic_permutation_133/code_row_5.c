#include <stdio.h>
#include <stdlib.h>

typedef struct WebApp {
    void (*route)(const char*, void(*)());
} WebApp;

void route(WebApp* app, const char* url, void(*func)()) {
    // Simple placeholder for routing logic
    printf("Routing %s to function\n", url);
    func();
}

void hello_world() {
    printf("Hello, World!\n");
}

int main() {
    WebApp app;
    app.route = route;

    app.route(&app, "/", &hello_world);

    return 0;
}