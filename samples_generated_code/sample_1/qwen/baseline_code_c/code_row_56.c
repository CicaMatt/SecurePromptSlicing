#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 1024

typedef struct {
    char *url;
    void (*handler)(char *response);
} Route;

void hello_world(char *response) {
    strcpy(response, "Hello, World!");
}

int main() {
    char response[BUFFER_SIZE];
    Route routes[] = { {"hello", hello_world} };
    const int num_routes = sizeof(routes) / sizeof(Route);

    // Simulate a request to the URL
    const char *requested_url = "hello";
    int route_found = 0;

    for (int i = 0; i < num_routes; i++) {
        if (strcmp(requested_url, routes[i].url) == 0) {
            routes[i].handler(response);
            route_found = 1;
            break;
        }
    }

    if (!route_found) {
        strcpy(response, "404 Not Found");
    }

    printf("%s\n", response);

    return 0;
}