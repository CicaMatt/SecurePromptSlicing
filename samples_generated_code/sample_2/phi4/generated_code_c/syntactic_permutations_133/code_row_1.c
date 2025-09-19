#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *path;
    void (*handler)(void);
} route_t;

typedef struct {
    int num_routes;
    route_t routes[10];
} wsgi_app_t;

void handle_root(void) {
    printf("Hello, World!\n");
}

int match_path(const char *request_path, const char *route_path) {
    return strcmp(request_path, route_path) == 0;
}

void run_wsgi_application(wsgi_app_t app, const char *request_path) {
    for (int i = 0; i < app.num_routes; ++i) {
        if (match_path(request_path, app.routes[i].path)) {
            app.routes[i].handler();
            return;
        }
    }
    printf("404 Not Found\n");
}

void setup_routes(wsgi_app_t *app) {
    app->num_routes = 1;
    strcpy(app->routes[0].path, "/");
    app->routes[0].handler = handle_root;
}

int main(int argc, char **argv) {
    wsgi_app_t app;
    setup_routes(&app);

    const char *request_path = "/";
    run_wsgi_application(app, request_path);

    return 0;
}