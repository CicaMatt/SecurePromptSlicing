#include <stdio.h>
#include <string.h>

#define MAX_URL_LENGTH 1024

typedef struct {
    char *url;
} Route;

typedef void (*Handler)(void);

Route routes[10];
int route_count = 0;

void add_route(const char *url, Handler handler) {
    if (route_count < 10) {
        routes[route_count].url = strdup(url);
        route_count++;
        handler();
    }
}

void handle_request(const char *request_url) {
    for (int i = 0; i < route_count; i++) {
        if (strcmp(routes[i].url, request_url) == 0) {
            printf("URL matches: %s\n", request_url);
            return;
        }
    }
    printf("No matching URL found.\n");
}

void my_function() {
    printf("Handling request for /my-url\n");
}

int main() {
    add_route("/my-url", my_function);
    handle_request("/my-url");
    handle_request("/non-existent-url");
    return 0;
}