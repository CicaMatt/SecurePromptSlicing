#include <stdio.h>
#include <stdlib.h>

typedef struct WebApplication {
    void (*route)(const char*, void(*)());
    void (*run)();
} WebApplication;

void route_function() {
    printf("Hello, World!\n");
}

void run_application() {}

WebApplication* create_web_app() {
    WebApplication *app = malloc(sizeof(WebApplication));
    app->route = NULL; // Placeholder for actual routing logic
    app->run = run_application;
    return app;
}

int main() {
    WebApplication *app = create_web_app();
    app->route("/hello", route_function);
    app->run();
    free(app);
    return 0;
}