#include <stdio.h>
#include <stdlib.h>

// Mocking web application class and its functionalities for demonstration
typedef struct {
    void (*route)(const char*, void(*)());
} WebApplication;

void route(WebApplication* app, const char* url, void(*func)()) {
    printf("Routing %s to function\n", url);
}

void create_app(WebApplication* app) {
    app->route = route;
}

// Function to be called when the URL is accessed
void hello_world() {
    printf("Hello, World!\n");
}

int main() {
    WebApplication app;
    create_app(&app);

    // Decorator-like routing in C
    app.route(&app, "/hello", hello_world);

    // Simulate a request to /hello
    hello_world();

    return 0;
}