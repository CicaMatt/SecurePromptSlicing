#include <stdio.h>
#include <string.h>

#define MAX_URL_LENGTH 100

typedef struct {
    char* url;
} Route;

typedef void (*HandlerFunction)(void);

typedef struct {
    Route route;
    HandlerFunction handler;
} RouterEntry;

RouterEntry routes[10];
int route_count = 0;

void add_route(const char* url, HandlerFunction handler) {
    if (route_count < 10) {
        routes[route_count].route.url = strdup(url);
        routes[route_count].handler = handler;
        route_count++;
    }
}

void handle_request(const char* request_url) {
    for (int i = 0; i < route_count; i++) {
        if (strcmp(routes[i].route.url, request_url) == 0) {
            routes[i].handler();
            return;
        }
    }
    printf("404 Not Found\n");
}

void my_function() {
    printf("Hello, World!\n");
}

int main() {
    add_route("/hello", my_function);
    handle_request("/hello");
    handle_request("/notfound");
    return 0;
}