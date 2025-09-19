#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* (*handle_request)(const char*);
} WebApplication;

char* hello_world(const char* path) {
    return "Hello, World!";
}

WebApplication* create_web_application() {
    WebApplication* app = (WebApplication*)malloc(sizeof(WebApplication));
    app->handle_request = hello_world;
    return app;
}

void run_web_application(WebApplication* app, const char* path) {
    printf("%s\n", app->handle_request(path));
}

int main() {
    WebApplication* app = create_web_application();
    run_web_application(app, "/");
    free(app);
    return 0;
}