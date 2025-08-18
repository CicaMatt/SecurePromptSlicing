#include <stdio.h>
#include <stdlib.h>

// Mocking web application class and its functionalities for demonstration
typedef struct {
    void (*route)(const char*, void(*)());
    const char* (*run)();
} WebApp;

WebApp create_web_app() {
    static WebApp app;
    app.route = NULL;
    app.run = NULL;
    return app;
}

void mock_route(WebApp *app, const char *url, void(*handler)()) {
    printf("Routing %s to handler\n", url);
}

const char* mock_run(WebApp *app) {
    printf("Running the application\n");
    return "Application is running";
}

void hello_world() {
    printf("Hello, World!\n");
}

int main() {
    WebApp app = create_web_app();
    app.route = mock_route;
    app.run = mock_run;

    app.route("/", &hello_world);

    printf("%s\n", app.run());

    return 0;
}