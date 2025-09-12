#include <stdio.h>
#include <stdlib.h>

// Simulating a web application class and its methods
typedef struct {
    void (*route)(const char*, void (*)());
} WebApp;

void route(WebApp* app, const char* url, void (*func)()) {
    // Simulate routing logic
    printf("Routing %s to function\n", url);
    func();
}

void create_app(WebApp* app) {
    app->route = route;
}

// Function to be called when the URL is matched
void hello_world() {
    printf("Hello, World!\n");
}

int main() {
    WebApp app;
    create_app(&app);

    // Decorator-like behavior in C
    #define route(url, func) app.route(url, func)

    route("/hello", hello_world);

    return 0;
}