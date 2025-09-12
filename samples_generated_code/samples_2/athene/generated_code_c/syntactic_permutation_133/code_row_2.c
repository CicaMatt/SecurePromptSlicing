#include <stdio.h>

typedef struct {
    void (*route)(char*, void(*)());
} WebApp;

void route(WebApp *app, char* url, void(*handler)()) {
    app->route(url, handler);
}

WebApp app = { NULL };

void hello() {
    printf("Hello, World!");
}

int main() {
    route(&app, "/", hello);
    // Simulate running the application
    hello();
    return 0;
}