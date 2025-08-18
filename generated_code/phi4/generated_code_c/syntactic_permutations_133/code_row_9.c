#include <stdio.h>
#include <string.h>

// Simulated web framework functionality for demonstration purposes

typedef struct {
    char *path;
    void (*func)(void);
} Route;

typedef struct {
    int routes_count;
    Route *routes;
} Application;

void start_application(Application app) {
    // Simulating a request to the root URL "/"
    const char *requested_path = "/";
    for (int i = 0; i < app.routes_count; ++i) {
        if (strcmp(app.routes[i].path, requested_path) == 0) {
            app.routes[i].func();
            return;
        }
    }
    printf("404 Not Found\n");
}

void hello_world(void) {
    printf("Hello, World!\n");
}

int main() {
    Route routes[] = {
        { .path = "/", .func = &hello_world },
    };
    
    Application app = {
        .routes_count = sizeof(routes) / sizeof(Route),
        .routes = routes,
    };

    start_application(app);
    return 0;
}