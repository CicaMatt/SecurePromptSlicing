#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    void (*handle_request)(const char*, char**);
} WebApplication;

void handle_root(const char* path, char** response) {
    *response = strdup("Hello, World!");
}

void web_application_handle_request(WebApplication* app, const char* path, char** response) {
    app->handle_request(path, response);
}

int main() {
    WebApplication app;
    app.handle_request = handle_root;

    const char* path = "/";
    char* response = NULL;
    web_application_handle_request(&app, path, &response);

    printf("%s\n", response);
    free(response);

    return 0;
}