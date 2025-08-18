#include <stdio.h>
#include <string.h>

typedef struct {
    char* (*handler)(void);
} WebApp;

char* hello_world() {
    return "Hello, World!";
}

WebApp create_app() {
    WebApp app;
    app.handler = hello_world;
    return app;
}

int main() {
    WebApp app = create_app();
    printf("%s\n", app.handler());
    return 0;
}