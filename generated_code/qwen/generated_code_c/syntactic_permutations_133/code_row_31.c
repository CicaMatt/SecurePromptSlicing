#include <stdio.h>
#include <string.h>

typedef struct {
    void (*route)(const char*, void*);
    void (*run)();
} WebApp;

void route_function(const char* path, void* handler) {
    printf("Routing path %s to handler\n", path);
}

void run_application() {
    printf("Running the application\n");
}

void create_app(WebApp* app) {
    app->route = route_function;
    app->run = run_application;
}

void hello_world() {
    printf("Hello, World!\n");
}

int main() {
    WebApp my_app;
    create_app(&my_app);
    my_app.route("/", (void*)hello_world);
    my_app.run();
    return 0;
}