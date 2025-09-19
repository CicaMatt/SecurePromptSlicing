#include <stdio.h>

typedef struct {
    // Web application properties and methods would be defined here
} web_application;

void run(web_application *app) {
    // Code to run the application would go here
}

#define route(url) void handle_request_##url()

route(/)
{
    printf("Hello, World!");
}

int main() {
    web_application app;
    run(&app);
    return 0;
}