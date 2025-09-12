#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    const char *path;
    void (*handler)();
} Route;

void hello_world() {
    printf("Content-Type: text/plain\r\n\r\n");
    printf("Hello, World!\n");
}

int main(int argc, char **argv) {
    Route routes[] = { {"/", hello_world}, {NULL, NULL} };
    const char *path_info = getenv("PATH_INFO") ?: "/";

    for (Route *route = routes; route->path != NULL; ++route) {
        if (strcmp(route->path, path_info) == 0) {
            route->handler();
            return 0;
        }
    }

    printf("Content-Type: text/plain\r\n\r\n");
    printf("404 Not Found\n");
    return 1;
}