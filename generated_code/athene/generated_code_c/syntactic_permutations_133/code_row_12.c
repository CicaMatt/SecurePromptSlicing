#include <stdio.h>

typedef struct {
    // Web application properties and methods
} WebApp;

WebApp* create_app() {
    return (WebApp*)malloc(sizeof(WebApp));
}

void route(WebApp *app, const char *url, void (*handler)(void)) {
    printf("Routing %s to handler\n", url);
    handler();
}

void hello_world_handler() {
    printf("Hello, World!\n");
}

int main() {
    WebApp *app = create_app();
    route(app, "/", hello_world_handler);
    return 0;
}