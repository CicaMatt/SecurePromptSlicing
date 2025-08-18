#include <stdio.h>
#include <stdlib.h>

typedef struct {
    void (*route)(const char*, void(*handler)());
    void(*run)();
} WebApplication;

void handle_request() {
    printf("Hello, World!\n");
}

void route(WebApplication *app, const char* url, void(*handler)()) {
    if (strcmp(url, "/") == 0) {
        handler();
    }
}

void run(WebApplication *app) {
    // Simulate a request to the root URL
    route(app, "/", handle_request);
}

int main() {
    WebApplication app = {route, run};
    app.route(&app, "/", handle_request);
    app.run(&app);
    return 0;
}