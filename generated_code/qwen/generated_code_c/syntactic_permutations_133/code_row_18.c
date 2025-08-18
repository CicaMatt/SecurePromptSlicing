#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* (*handle_request)(const char*);
} WebApplication;

char* home_handler(const char* url) {
    return "Hello, World!";
}

WebApplication create_web_app() {
    WebApplication app;
    app.handle_request = home_handler;
    return app;
}

int main(int argc, char** argv) {
    WebApplication app = create_web_app();
    const char* url = "/";
    printf("%s\n", app.handle_request(url));
    return 0;
}