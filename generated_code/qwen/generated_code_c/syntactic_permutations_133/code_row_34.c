#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* (*handle_request)(const char*);
} WebApp;

char* index_page(const char* path) {
    return "Hello, World!";
}

WebApp create_web_app() {
    WebApp app;
    app.handle_request = index_page;
    return app;
}

int main() {
    WebApp app = create_web_app();
    const char* response = app.handle_request("/");
    printf("%s\n", response);
    return 0;
}