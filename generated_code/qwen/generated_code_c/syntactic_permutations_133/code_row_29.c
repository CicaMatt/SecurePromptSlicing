#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* (*handle_request)(const char*);
} WebApplication;

char* handle_root(const char* path) {
    return "Hello, World!";
}

WebApplication create_web_application() {
    WebApplication app;
    app.handle_request = handle_root;
    return app;
}

int main(int argc, char** argv) {
    WebApplication app = create_web_application();
    const char* request_path = "/";
    if (strcmp(request_path, "/") == 0) {
        printf("%s\n", app.handle_request(request_path));
    }
    return 0;
}