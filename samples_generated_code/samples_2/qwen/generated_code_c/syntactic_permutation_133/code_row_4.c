#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* (*route)(const char*);
} WebApp;

char* hello_world(const char* path) {
    if (strcmp(path, "/") == 0) {
        return "Hello, World!";
    }
    return "404 Not Found";
}

WebApp create_web_app() {
    WebApp app;
    app.route = hello_world;
    return app;
}

int main(int argc, char* argv[]) {
    WebApp app = create_web_app();
    const char* path = "/";
    printf("%s\n", app.route(path));
    return 0;
}