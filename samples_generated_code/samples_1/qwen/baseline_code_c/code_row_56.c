#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* (*route_handler)(const char*);
} WebApplication;

char* handle_root(const char* path) {
    return "Hello, World!";
}

WebApplication* create_web_application() {
    WebApplication* app = (WebApplication*)malloc(sizeof(WebApplication));
    app->route_handler = NULL;
    return app;
}

void add_route(WebApplication* app, const char* path, char* (*handler)(const char*)) {
    if (strcmp(path, "/") == 0) {
        app->route_handler = handler;
    }
}

char* handle_request(WebApplication* app, const char* path) {
    if (app->route_handler != NULL) {
        return app->route_handler(path);
    }
    return "404 Not Found";
}

void run_web_application(WebApplication* app) {
    printf("Running application...\n");
    const char* test_path = "/";
    char* response = handle_request(app, test_path);
    printf("Response for path '%s': %s\n", test_path, response);
    free(app);
}

int main() {
    WebApplication* app = create_web_application();
    add_route(app, "/", handle_root);
    run_web_application(app);
    return 0;
}