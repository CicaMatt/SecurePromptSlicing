#include <stdio.h>
#include <string.h>

typedef struct {
    const char* (*handle_request)(const char*);
} WebApplication;

const char* hello_world(const char* path) {
    if (strcmp(path, "/") == 0) {
        return "Hello World!";
    }
    return "Not Found";
}

WebApplication create_web_app() {
    WebApplication app;
    app.handle_request = hello_world;
    return app;
}

int main() {
    WebApplication app = create_web_app();
    const char* response = app.handle_request("/");
    printf("%s\n", response);
    return 0;
}