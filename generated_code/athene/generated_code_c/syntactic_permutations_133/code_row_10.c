#include <stdio.h>

typedef struct {
    // WSGI application context
} wsgi_app;

wsgi_app* create_app() {
    return (wsgi_app*) malloc(sizeof(wsgi_app));
}

void route(wsgi_app *app, char* url, void (*handler)(char*)) {
    printf("Routing %s to handler\n", url);
    handler(url);
}

void hello_world_handler(char* url) {
    printf("Hello, World! You visited: %s\n", url);
}

int main() {
    wsgi_app *app = create_app();
    route(app, "/", hello_world_handler);
    return 0;
}