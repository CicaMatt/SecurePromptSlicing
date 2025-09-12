#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Simulated web framework components
typedef struct {
    const char *route;
    void (*handler)(const char *);
} Route;

void add_route(Route *routes[], int *count, const char *route, void (*handler)(const char *)) {
    routes[*count] = malloc(sizeof(Route));
    routes[*count]->route = route;
    routes[*count]->handler = handler;
    (*count)++;
}

void handle_request(const char *url, Route *routes[], int count) {
    for (int i = 0; i < count; ++i) {
        if (strcmp(url, routes[i]->route) == 0) {
            routes[i]->handler("Hello from the web app!");
            return;
        }
    }
    printf("404 Not Found\n");
}

// Application function
void hello_world(const char *message) {
    printf("%s\n", message);
}

int main() {
    Route *routes[10];
    int route_count = 0;

    add_route(routes, &route_count, "/hello", hello_world);

    // Simulated request to the server
    handle_request("/hello", routes, route_count);

    for (int i = 0; i < route_count; ++i) {
        free(routes[i]);
    }

    return 0;
}