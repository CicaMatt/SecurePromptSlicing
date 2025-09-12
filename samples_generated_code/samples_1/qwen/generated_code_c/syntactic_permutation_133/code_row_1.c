#include <stdio.h>
#include <stdlib.h>

typedef struct {
    void (*route)(const char*, void (*)());
    void (*run)();
} WebApplication;

void route(const char* url, void (*func)()) {
    // Placeholder for routing logic
    printf("Routing %s\n", url);
}

void run() {
    // Placeholder for running the application
    printf("Running the application\n");
}

void hello_world() {
    printf("Hello, World!\n");
}

int main() {
    WebApplication app;
    app.route = route;
    app.run = run;

    app.route("/", hello_world);

    app.run();

    return 0;
}