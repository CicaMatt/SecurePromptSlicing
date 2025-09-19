#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* (*route)(const char*);
} WebApplication;

char* index() {
    return "Hello, World!";
}

char* route(WebApplication* app, const char* url) {
    if (strcmp(url, "/") == 0) {
        return app->route();
    }
    return "404 Not Found";
}

int main() {
    WebApplication app;
    app.route = index;

    const char* request_url = "/";
    printf("%s\n", route(&app, request_url));

    return 0;
}