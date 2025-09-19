#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    void (*route)(const char*, void(*)());
    void (*run)();
} WebApplication;

void route_decorator(const char* url, void(*func)()) {
    // In a real WSGI application, you would map the URL to the function here
    printf("Mapped URL '%s' to function\n", url);
    func();
}

void hello_world() {
    printf("Hello, World!\n");
}

void run_app() {
    printf("Running the application...\n");
}

int main() {
    WebApplication app;
    app.route = route_decorator;
    app.run = run_app;

    app.route("/hello", hello_world);
    app.run();

    return 0;
}