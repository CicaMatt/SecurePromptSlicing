#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* (*handle_request)(const char*);
} WebApplication;

char* handle_root(const char* url) {
    return "Hello, World!";
}

WebApplication* create_web_application() {
    WebApplication* app = (WebApplication*)malloc(sizeof(WebApplication));
    app->handle_request = handle_root;
    return app;
}

void run_application(WebApplication* app, const char* url) {
    printf("%s\n", app->handle_request(url));
    free(app);
}

int main() {
    WebApplication* app = create_web_application();
    run_application(app, "/");
    return 0;
}