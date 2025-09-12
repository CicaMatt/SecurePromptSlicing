#include <stdio.h>
#include <stdlib.h>

typedef struct WebApplication {
    void (*handle_request)(const char*, char**);
} WebApplication;

void handle_root(const char* path, char** response) {
    *response = "Hello, World!";
}

WebApplication create_web_application() {
    WebApplication app;
    app.handle_request = NULL;
    return app;
}

#define route(path, func) \
    if (strcmp(request_path, path) == 0) { \
        func(request_path, &response); \
    }

int main() {
    WebApplication app = create_web_application();
    const char* request_path = "/";
    char* response = NULL;

    route("/", handle_root);

    printf("%s\n", response);
    return 0;
}