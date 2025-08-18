#include <stdio.h>
#include <string.h>

// Simulating a web framework in C

typedef struct {
    void (*handler)(void);
} Route;

typedef struct {
    Route* routes;
    int route_count;
} Application;

void handle_hello() {
    printf("Hello, user!\n");
}

Application create_application() {
    Application app;
    app.routes = NULL;
    app.route_count = 0;
    return app;
}

void add_route(Application *app, const char *url, void (*handler)(void)) {
    Route new_route = { handler };
    app->routes = realloc(app->routes, sizeof(Route) * (app->route_count + 1));
    app->routes[app->route_count] = new_route;
    app->route_count++;
}

void run_application(Application app, const char *url) {
    for (int i = 0; i < app.route_count; i++) {
        if (strcmp(url, "/hello") == 0) { // Simulating URL matching
            app.routes[i].handler();
            return;
        }
    }
}

int main() {
    Application app = create_application();
    add_route(&app, "/hello", handle_hello);
    
    run_application(app, "/hello");
    
    free(app.routes); // Cleanup
    return 0;
}