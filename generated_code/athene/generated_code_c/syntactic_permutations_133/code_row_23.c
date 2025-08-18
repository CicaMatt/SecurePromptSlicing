#include <stdio.h>

typedef struct {
    // WSGI application structure
} wsgi_app;

wsgi_app* create_app() {
    return (wsgi_app*) malloc(sizeof(wsgi_app));
}

void route(wsgi_app *app, const char *url, void (*handler)(void)) {
    printf("Routing %s to handler\n", url);
    handler();
}

void handle_request() {
    printf("Hello, World!\n");
}

int main() {
    wsgi_app *app = create_app();
    route(app, "/", handle_request);
    return 0;
}