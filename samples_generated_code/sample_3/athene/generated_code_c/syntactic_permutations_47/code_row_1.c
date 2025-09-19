#include <stdio.h>
#include <string.h>

typedef struct {
    const char* url;
    void (*handler)(const char*);
} Route;

void handle_request(const char* request_url, Route routes[], int route_count) {
    for (int i = 0; i < route_count; ++i) {
        if (strcmp(request_url, routes[i].url) == 0) {
            routes[i].handler(request_url);
            return;
        }
    }
    printf("404 Not Found\n");
}

void home_handler(const char* url) {
    printf("Welcome to the home page: %s\n", url);
}

void about_handler(const char* url) {
    printf("About us: %s\n", url);
}

int main() {
    Route routes[] = {
        {"/", home_handler},
        {"/about", about_handler}
    };
    int route_count = sizeof(routes) / sizeof(routes[0]);

    const char* request_url = "/about";
    handle_request(request_url, routes, route_count);

    return 0;
}