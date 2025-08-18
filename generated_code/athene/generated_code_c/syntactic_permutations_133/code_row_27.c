#include <stdio.h>

typedef struct {
    // Web application properties and methods would go here
} web_application;

void run(web_application *app) {
    // Run the application logic would go here
}

#define route(path, func) void func()

route("/", index) {
    printf("Hello, World!");
}

int main() {
    web_application app;
    index();
    run(&app);
    return 0;
}