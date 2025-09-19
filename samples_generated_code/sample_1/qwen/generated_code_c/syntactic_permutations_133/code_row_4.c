#include <stdio.h>
#include <string.h>

// Mocking a web application class and its functionalities for demonstration purposes

typedef struct {
    void (*route)(const char*, void(*)());
} WebApp;

void route(WebApp* app, const char* url, void(*func)()) {
    // Dummy implementation to simulate routing
    printf("Routing %s\n", url);
}

void run(WebApp* app) {
    // Dummy implementation to simulate running the application
    printf("Running web application\n");
}

WebApp create_web_app() {
    WebApp app;
    app.route = route;
    return app;
}

void home_page() {
    printf("Hello, World!\n");
}

int main() {
    WebApp app = create_web_app();
    app.route("/", home_page);
    run(&app);
    return 0;
}