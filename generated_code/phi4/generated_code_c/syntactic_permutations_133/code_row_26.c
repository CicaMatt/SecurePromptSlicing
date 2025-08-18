#include <stdio.h>
#include <stdlib.h>

typedef struct {
    void (*run)(void);
} WebApplication;

WebApplication create_app() {
    WebApplication app;
    app.run = run_app;
    return app;
}

void route(const char* url) {
    printf("Route: %s\n", url);
}

void run_app() {
    printf("Hello, World!\n");
}

int main() {
    WebApplication app = create_app();
    route("/hello");
    app.run();
    return 0;
}