#include <stdio.h>
#include <stdlib.h>

// Mocking web application class and its functionalities for demonstration
typedef struct {
    void (*route)(const char*, void (*)());
} WebApp;

void route(WebApp* app, const char* url, void (*func)()) {
    // Dummy implementation to mimic routing
    printf("Routing URL %s to function\n", url);
    func();
}

void create_app(WebApp* app) {
    app->route = &route;
}

void hello_world() {
    printf("Hello, World!\n");
}

int main() {
    WebApp app;
    create_app(&app);

    // Define route
    app.route("/hello", hello_world);

    return 0;
}