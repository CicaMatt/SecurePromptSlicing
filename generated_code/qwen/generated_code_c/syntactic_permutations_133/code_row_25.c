#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Mocking a simple WSGI-like application in C

typedef struct {
    char* (*get_response)(const char*);
} WebApplication;

char* hello_world(const char* path) {
    if (strcmp(path, "/") == 0) {
        return "Hello, World!";
    }
    return "404 Not Found";
}

WebApplication create_web_app() {
    WebApplication app;
    app.get_response = hello_world;
    return app;
}

int main() {
    WebApplication app = create_web_app();
    const char* path = "/"; // Simulating a URL path
    printf("%s\n", app.get_response(path));
    return 0;
}