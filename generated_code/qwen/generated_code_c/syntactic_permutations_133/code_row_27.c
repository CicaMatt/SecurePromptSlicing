#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Mocking a simple web framework in C

typedef struct {
    char* (*get_response)(const char*);
} WebApplication;

char* handle_root(const char* path) {
    return "Hello, World!";
}

WebApplication* create_web_application() {
    WebApplication* app = (WebApplication*)malloc(sizeof(WebApplication));
    app->get_response = NULL;
    return app;
}

void route(WebApplication* app, const char* path, char* (*handler)(const char*)) {
    if (strcmp(path, "/") == 0) {
        app->get_response = handler;
    }
}

int main() {
    WebApplication* app = create_web_application();
    route(app, "/", handle_root);
    
    // Simulating a request to the root URL
    const char* path = "/";
    char* response = app->get_response(path);
    printf("%s\n", response);

    free(app);
    return 0;
}