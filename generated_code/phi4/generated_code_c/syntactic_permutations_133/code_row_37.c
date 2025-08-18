#include <stdio.h>
#include <string.h>

typedef struct {
    const char* (*request_handler)(const char*);
} WSGIApp;

const char* hello_world(const char* request) {
    return "Hello, World!";
}

WSGIApp create_app() {
    WSGIApp app;
    app.request_handler = hello_world;
    return app;
}

void route(WSGIApp* app, const char* path) {
    if (strcmp(path, "/hello") == 0) {
        printf("%s\n", app->request_handler(NULL));
    }
}

int main() {
    WSGIApp app = create_app();
    route(&app, "/hello");
    return 0;
}