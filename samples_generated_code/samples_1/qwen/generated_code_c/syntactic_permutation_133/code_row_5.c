#include <stdio.h>
#include <stdlib.h>

typedef struct {
    void (*route)(const char*, void(*)());
    void (*run)();
} WebApplication;

void hello_world() {
    printf("Hello, World!\n");
}

void route(const char* url, void(*func)()) {
    if (strcmp(url, "/") == 0) {
        func();
    }
}

void run() {
    // Simulating running the application
    route("/", hello_world);
}

int main() {
    WebApplication app = {route, run};
    app.run();
    return 0;
}