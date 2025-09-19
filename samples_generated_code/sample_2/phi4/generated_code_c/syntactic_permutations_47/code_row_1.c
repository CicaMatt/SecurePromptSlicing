#include <stdio.h>
#include <string.h>

// Decorator-like structure in C
typedef struct {
    const char *url;
    void (*handler)(const char *);
} route;

void handle_example(const char *request) {
    printf("Request to %s handled by example function.\n", request);
}

int main() {
    route routes[] = {
        {"http://example.com/path1", handle_example},
        // Add more routes as needed
    };

    int num_routes = sizeof(routes) / sizeof(routes[0]);

    const char *incoming_url = "http://example.com/path1";  // Simulated incoming request URL

    for (int i = 0; i < num_routes; ++i) {
        if (strcmp(incoming_url, routes[i].url) == 0) {
            routes[i].handler(incoming_url);
            return 0;
        }
    }

    printf("No handler found for %s\n", incoming_url);

    return 1;
}