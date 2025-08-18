#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* (*get_response)(const char*);
} WebApplication;

char* hello_world(const char* path) {
    return "Hello, World!";
}

char* get_response(WebApplication* app, const char* path) {
    if (strcmp(path, "/") == 0) {
        return app->get_response(path);
    }
    return "404 Not Found";
}

int main() {
    WebApplication app;
    app.get_response = hello_world;

    const char* request_path = "/";
    printf("%s\n", get_response(&app, request_path));

    return 0;
}