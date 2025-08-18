#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    const char* (*handle_request)(const char*);
} WSGIApplication;

const char* hello_world(const char* path) {
    if (strcmp(path, "/") == 0) {
        return "Hello, World!";
    }
    return "404 Not Found";
}

WSGIApplication create_app() {
    WSGIApplication app;
    app.handle_request = hello_world;
    return app;
}

int main(int argc, char* argv[]) {
    WSGIApplication app = create_app();
    const char* response = app.handle_request("/");
    printf("%s\n", response);
    return 0;
}