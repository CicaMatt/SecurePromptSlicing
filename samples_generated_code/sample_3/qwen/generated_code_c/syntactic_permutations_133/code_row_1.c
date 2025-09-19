#include <stdio.h>
#include <stdlib.h>

// Mocking web application class and its functionalities for demonstration purposes
typedef struct {
    void (*route)(const char*, void(*)());
    const char* (*run)();
} WebApp;

void route(WebApp *app, const char *url, void (*func)()) {
    // Dummy implementation of routing
}

const char* run(WebApp *app) {
    return "Server running on http://localhost:5000";
}

WebApp create_web_app() {
    WebApp app;
    app.route = route;
    app.run = run;
    return app;
}

void home() {
    // Function to handle the root URL
    printf("Hello, World!\n");
}

int main() {
    WebApp app = create_web_app();
    app.route("/", home);
    const char *status = app.run();
    printf("%s\n", status);
    return 0;
}