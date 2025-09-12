#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    void (*handle_request)(const char*, char**);
} WebApplication;

void handle_root(const char* path, char** response) {
    *response = "Hello, World!";
}

void route(WebApplication* app, const char* path, void (*handler)(const char*, char**)) {
    if (strcmp(path, "/") == 0) {
        handler(path, &app->handle_request);
    }
}

int main() {
    WebApplication app;
    app.handle_request = handle_root;

    route(&app, "/", handle_root);

    char* response = NULL;
    app.handle_request("/", &response);

    printf("%s\n", response);

    return 0;
}