#include <stdio.h>
#include <string.h>

void start_server();

typedef struct {
    const char* url;
    void (*handler)(const char*);
} route_t;

route_t routes[] = {
    {"/", handle_root},
    {NULL, NULL}
};

void handle_root(const char* request) {
    printf("Hello, World!\n");
}

int match_route(const char* path) {
    for (int i = 0; routes[i].url != NULL; ++i) {
        if (strcmp(routes[i].url, path) == 0) {
            return i;
        }
    }
    return -1;
}

void handle_request(const char* request_path) {
    int index = match_route(request_path);
    if (index >= 0 && routes[index].handler != NULL) {
        routes[index].handler(request_path);
    } else {
        printf("404 Not Found\n");
    }
}

int main() {
    // Simulating a web server with HTTP requests
    const char* test_requests[] = {"/", "/about", NULL};

    for (int i = 0; test_requests[i] != NULL; ++i) {
        printf("Request: %s\n", test_requests[i]);
        handle_request(test_requests[i]);
        printf("\n");
    }

    return 0;
}