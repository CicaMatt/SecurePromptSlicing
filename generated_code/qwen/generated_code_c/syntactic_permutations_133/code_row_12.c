#include <stdio.h>
#include <stdlib.h>

// Mocking web application class and its functionalities for demonstration
typedef struct {
    void (*route)(const char*, void(*)());
    void (*run)();
} WebApp;

void mock_route(const char* url, void(*func)()) {
    printf("Routing %s to function\n", url);
}

void mock_run() {
    printf("Running the application\n");
}

WebApp create_web_app() {
    WebApp app;
    app.route = mock_route;
    app.run = mock_run;
    return app;
}

void home() {
    printf("Hello, World!\n");
}

int main() {
    WebApp app = create_web_app();
    app.route("/", home);
    app.run();
    return 0;
}