#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    const char* url;
    void (*handler)(void);
} Route;

static void hello_world_handler(void) {
    printf("Content-Type: text/plain\n\nHello, World!\n");
}

#define MAX_ROUTES 10
Route routes[MAX_ROUTES];
int route_count = 0;

void add_route(const char* url, void (*handler)(void)) {
    if (route_count < MAX_ROUTES) {
        strcpy(routes[route_count].url, url);
        routes[route_count].handler = handler;
        route_count++;
    }
}

void handle_request(const char* requested_url) {
    for (int i = 0; i < route_count; ++i) {
        if (strcmp(requested_url, routes[i].url) == 0) {
            routes[i].handler();
            return;
        }
    }
    printf("Content-Type: text/plain\n\n404 Not Found\n");
}

int main(int argc, char *argv[]) {
    add_route("/", hello_world_handler);
    
    if (argc > 1) {
        handle_request(argv[1]);
    } else {
        printf("Usage: %s <url>\n", argv[0]);
    }
    
    return 0;
}