#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    const char* (*handle_request)(const char*);
} WebApplication;

const char* handle_root(const char* path) {
    if (strcmp(path, "/") == 0) {
        return "Hello, World!";
    }
    return "404 Not Found";
}

const char* web_app_handle_request(WebApplication* app, const char* path) {
    return app->handle_request(path);
}

int main() {
    WebApplication app;
    app.handle_request = handle_root;

    const char* response = web_app_handle_request(&app, "/");
    printf("%s\n", response);

    return 0;
}