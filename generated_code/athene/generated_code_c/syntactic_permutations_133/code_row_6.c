#include <stdio.h>
#include <stdlib.h>

typedef struct {
    // Placeholder for WSGI application state
} wsgi_app;

void start_response(char *status, char **headers) {
    // Placeholder function for starting response in WSGI app
}

int app(wsgi_app *app, char *env[], int (*start_response)(char *, char **)) {
    const char *response = "Hello, World!";
    char *headers[] = {"Content-Type: text/plain"};
    start_response("200 OK", headers);
    return printf("%s", response);
}

wsgi_app *create_app() {
    wsgi_app *app = (wsgi_app *)malloc(sizeof(wsgi_app));
    return app;
}

#define DECORATOR(url, func) void route_##func() { func(); }

DECORATOR("/", hello)
void hello() {
    printf("Hello, World!");
}

int main(int argc, char *argv[]) {
    wsgi_app *app = create_app();
    app(app, NULL, start_response);
    return 0;
}