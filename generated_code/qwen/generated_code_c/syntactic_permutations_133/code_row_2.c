#include <stdio.h>
#include <stdlib.h>

typedef struct {
    void (*route)(const char*, void(*)());
    void (*run)();
} WebApp;

void hello_world() {
    printf("Content-Type: text/html\r\n\r\n");
    printf("<html><body>Hello, World!</body></html>");
}

void route(const char* path, void(*func)()) {
    if (strcmp(path, "/") == 0) {
        func();
    }
}

void run() {
    // Simulating a web request to the root URL
    route("/", hello_world);
}

int main() {
    WebApp app;
    app.route = route;
    app.run = run;

    app.run();

    return 0;
}