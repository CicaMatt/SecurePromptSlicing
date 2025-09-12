#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    void (*route)(const char*, void(*)());
} WebApplication;

void route(WebApplication *app, const char *url, void(*func)()) {
    // In a real implementation, this would map URLs to functions
    printf("Routing %s to function\n", url);
    func();
}

void handleRoot() {
    printf("Hello, World!\n");
}

int main() {
    WebApplication app;
    route(&app, "/", handleRoot);
    return 0;
}