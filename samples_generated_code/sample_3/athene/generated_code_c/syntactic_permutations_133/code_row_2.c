#include <stdio.h>

typedef struct {
    // Placeholder for WSGI application structure
} wsgi_app;

wsgi_app* create_wsgi_app() {
    return (wsgi_app*)malloc(sizeof(wsgi_app));
}

void route(wsgi_app *app, char *url, void (*handler)(void)) {
    printf("Routing %s to handler\n", url);
    handler();
}

void hello_world_handler() {
    printf("Hello, World!\n");
}

int main() {
    wsgi_app *app = create_wsgi_app();
    route(app, "/", hello_world_handler);
    return 0;
}