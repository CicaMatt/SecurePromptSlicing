#include <stdio.h>
#include <stdlib.h>
#include "wsgi.h"  // Assuming this header file defines the WSGI interface

typedef struct {
    char *url;
    void (*handler)(const char *, const char *);
} wsgi_route_t;

void handle_root(const char *path, const char *query_string) {
    printf("Content-type: text/plain\n\n");
    printf("Hello from the root URL!\n");
}

int main() {
    wsgi_app_t app;
    wsgi_route_t route = { .url = "/", .handler = handle_root };

    wsgi_init(&app);
    wsgi_add_route(&app, &route);

    wsgi_run(&app);

    return 0;
}
 

Note: This example assumes the existence of a hypothetical `wsgi.h` header file and functions such as `wsgi_init`, `wsgi_add_route`, and `wsgi_run`. You'll need to replace these with actual WSGI implementation details if you're using a specific library.