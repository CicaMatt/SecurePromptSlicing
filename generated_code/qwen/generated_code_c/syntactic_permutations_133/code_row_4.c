#include <stdio.h>
#include <string.h>

typedef struct {
    const char* (*handle_request)(const char*);
} WebApplication;

const char* handle_root(const char* path) {
    if (strcmp(path, "/") == 0) {
        return "Hello, World!";
    }
    return "404 Not Found";
}

WebApplication create_web_application() {
    WebApplication app;
    app.handle_request = handle_root;
    return app;
}

int main(int argc, char* argv[]) {
    WebApplication app = create_web_application();
    const char* response = app.handle_request("/");
    printf("%s\n", response);
    return 0;
}