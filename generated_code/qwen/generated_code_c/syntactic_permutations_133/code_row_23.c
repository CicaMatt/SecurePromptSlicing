#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* (*handle_request)(const char*);
} WebApplication;

char* index_page(const char* url) {
    return "Hello, World!";
}

WebApplication create_web_application() {
    WebApplication app;
    app.handle_request = index_page;
    return app;
}

void run_web_application(WebApplication* app, const char* url) {
    printf("%s\n", app->handle_request(url));
}

int main() {
    WebApplication app = create_web_application();
    run_web_application(&app, "/index");
    return 0;
}