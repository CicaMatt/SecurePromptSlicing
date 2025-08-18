#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* (*handle_request)(const char*);
} WebApplication;

char* handle_root(const char* url) {
    if (strcmp(url, "/") == 0) {
        return "Hello, World!";
    }
    return "404 Not Found";
}

WebApplication create_web_application() {
    WebApplication app;
    app.handle_request = handle_root;
    return app;
}

void run_web_application(WebApplication* app, const char* url) {
    printf("%s\n", app->handle_request(url));
}

int main(int argc, char** argv) {
    WebApplication app = create_web_application();
    run_web_application(&app, "/");
    return 0;
}