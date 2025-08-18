#include <stdio.h>
#include <string.h>

// Simulating web application class and functions for demonstration
typedef struct {
    void (*route)(const char*, void (*)());
} WebApplication;

void route(WebApplication *app, const char *url, void (*func)()) {
    // This is a placeholder for routing logic
    printf("Routing %s to function\n", url);
    func();
}

void hello_world() {
    printf("Hello, World!\n");
}

int main() {
    WebApplication app;
    route(&app, "/", hello_world);
    return 0;
}