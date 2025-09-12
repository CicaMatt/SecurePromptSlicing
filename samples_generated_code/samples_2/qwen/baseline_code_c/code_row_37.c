#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char* (*route)(const char*);
} WebApplication;

char* hello_world(const char* path) {
    return "Hello, World!";
}

WebApplication create_app() {
    WebApplication app;
    app.route = hello_world;
    return app;
}

int main() {
    WebApplication app = create_app();
    const char* response = app.route("/");
    printf("%s\n", response);
    return 0;
}