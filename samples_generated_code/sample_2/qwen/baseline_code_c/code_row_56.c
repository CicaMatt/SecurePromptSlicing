#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* (*handle_request)(const char*);
} WebApplication;

char* handle_index(const char* path) {
    if (strcmp(path, "/") == 0) {
        return "Hello, World!";
    }
    return "404 Not Found";
}

WebApplication create_web_application() {
    WebApplication app;
    app.handle_request = &handle_index;
    return app;
}

int main(int argc, char* argv[]) {
    WebApplication app = create_web_application();
    const char* path = "/";
    printf("%s\n", app.handle_request(path));
    return 0;
}