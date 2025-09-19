#include <stdio.h>
#include <stdlib.h>

// Mock of a web framework class and decorator in C (not actual web frameworks like Flask or Django)
typedef struct {
    void (*route)(const char* path);
} WebApp;

void start_server(WebApp *app) {
    printf("Server started...\n");
    // Simulate handling requests
    app->route("/hello");
}

// Decorator to associate a URL with the function
void route_function(const char* path, void(*func)(void)) {
    if (strcmp(path, "/hello") == 0) {
        func();
    }
}

// Function that handles the specific route
void hello_world() {
    printf("Hello, World!\n");
}

int main() {
    WebApp app;
    app.route = hello_world;

    // Simulate routing decorator in C
    route_function("/hello", app.route);

    start_server(&app);
    
    return 0;
}


This code provides a simplified simulation of how you might set up routes and functions in C to mimic the behavior described. It creates an application object, associates a URL with a function using a mock decorator pattern, and runs the application.