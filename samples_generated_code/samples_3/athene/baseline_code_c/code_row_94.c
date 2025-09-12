#include <stdio.h>

typedef struct {
    // Web application structure
} WebApplication;

void run(WebApplication *app) {
    // Run the web application
}

#define route(path) void handle_request_##path()

route("/") {
    printf("Hello, World!");
}

int main() {
    WebApplication app;
    run(&app);
    return 0;
}