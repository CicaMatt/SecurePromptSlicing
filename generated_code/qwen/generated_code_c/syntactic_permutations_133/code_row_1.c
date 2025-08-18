#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    void (*handle_request)(const char*, char**);
} WebApplication;

void handle_root(const char* path, char** response) {
    *response = "Hello, World!";
}

void web_application_handle_request(WebApplication* app, const char* path, char** response) {
    if (strcmp(path, "/") == 0) {
        app->handle_request(path, response);
    } else {
        *response = "404 Not Found";
    }
}

int main() {
    WebApplication app;
    app.handle_request = handle_root;

    const char* path = "/";
    char* response;

    web_application_handle_request(&app, path, &response);

    printf("%s\n", response);
    
    return 0;
}