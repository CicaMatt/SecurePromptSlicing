#include <stdio.h>
#include <stdlib.h>

// Simulating web application class and its functionalities
typedef struct {
    void (*route)(const char*, void(*)());
    void (*run)();
} WebApp;

void route(WebApp* app, const char* url, void(*handler)()) {
    // In a real scenario, this would map the URL to the handler function
    printf("Route set for %s\n", url);
}

void run(WebApp* app) {
    // Simulate running the web application
    printf("Application is running...\n");
    // Here we manually call the handler as an example
    printf("Handling request at /\n");
    printf("Hello, World!\n");
}

WebApp create_web_app() {
    WebApp app;
    app.route = route;
    app.run = run;
    return app;
}

void home_handler() {
    // This function would be called when the root URL is accessed
    printf("Home handler called\n");
}

int main() {
    WebApp app = create_web_app();
    app.route("/", home_handler);
    app.run();
    return 0;
}