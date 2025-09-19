#include <stdio.h>
#include <stdlib.h>

typedef struct {
    void (*handle_request)(const char*, char**);
} WebApplication;

void handle_root(const char* path, char** response) {
    *response = "Hello, World!";
}

void route(WebApplication* app, const char* url, void (*handler)(const char*, char**)) {
    // In a real implementation, you would parse the URL and call the appropriate handler
    app->handle_request = handler;
}

int main() {
    WebApplication app;
    char* response;

    route(&app, "/", handle_root);
    app.handle_request("/", &response);

    printf("%s\n", response);

    return 0;
}