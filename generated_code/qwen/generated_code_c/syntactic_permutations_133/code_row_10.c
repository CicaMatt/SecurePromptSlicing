#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    void (*route)(const char*, void(*)());
    void (*run)();
} WebApplication;

void route(const char* url, void(*func)()) {
    // Dummy implementation for routing
    if (strcmp(url, "/") == 0) {
        func();
    }
}

void run() {
    // Dummy implementation to start the application
    printf("Running the web application...\n");
}

void index() {
    printf("Hello, World!\n");
}

int main() {
    WebApplication app;
    app.route = route;
    app.run = run;

    app.route("/", index);

    app.run();

    return 0;
}