#include <stdio.h>
#include <stdlib.h>

// Simulating web application class and its functionalities
typedef struct {
    void (*route)(const char*, void (*)());
    void (*run)();
} WebApp;

void route(WebApp* app, const char* url, void (*func)()) {
    // In a real scenario, this function would map URLs to functions
    printf("Mapping URL '%s' to function\n", url);
}

void run(WebApp* app) {
    // Simulate running the application
    printf("Running web application...\n");
}

WebApp create_web_app() {
    WebApp app;
    app.route = route;
    app.run = run;
    return app;
}

void hello_world() {
    printf("Hello, World!\n");
}

int main() {
    WebApp app = create_web_app();
    app.route("/", hello_world);
    app.run();
    return 0;
}