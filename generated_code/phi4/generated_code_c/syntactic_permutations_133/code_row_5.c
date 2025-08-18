#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *path;
    void (*func)(int, char **);
} route_t;

void hello_world(int argc, char **argv) {
    printf("Content-Type: text/plain\r\n"
           "\r\n"
           "Hello, world!\n");
}

route_t routes[] = {
    {"/", hello_world},
    {NULL, NULL}
};

typedef struct {
    const char *request_line;
} request_t;

void handle_request(request_t *req) {
    for (int i = 0; routes[i].path != NULL; ++i) {
        if (strcmp(req->request_line + 1, routes[i].path) == 0) { // Skip the leading '/'
            routes[i].func(2, (char *[]){NULL}); // Simulate argc=2 and argv[1]=req->request_line
            return;
        }
    }
    printf("Content-Type: text/plain\r\n"
           "\r\n"
           "404 Not Found\n");
}

int main(int argc, char **argv) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <port> <request_line>\n", argv[0]);
        return EXIT_FAILURE;
    }

    int port = atoi(argv[1]);
    handle_request((request_t){.request_line = argv[2]});
    
    return EXIT_SUCCESS;
}