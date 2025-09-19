#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PATH 256

typedef struct {
    const char *path;
    void (*handler)(const char *name);
} Route;

Route routes[10];
int route_count = 0;

void add_route(const char *path, void (*handler)(const char *name)) {
    if (route_count < 10) {
        routes[route_count].path = path;
        routes[route_count++].handler = handler;
    }
}

void img(const char *name) {
    char filepath[MAX_PATH];
    snprintf(filepath, sizeof(filepath), "images/%s", name);
    FILE *file = fopen(filepath, "rb");
    if (file == NULL) {
        printf("HTTP/1.1 404 Not Found\r\nContent-Length: 0\r\n\r\n");
        return;
    }
    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    rewind(file);

    printf("HTTP/1.1 200 OK\r\n");
    printf("Content-Type: image/jpeg\r\n");
    printf("Content-Length: %ld\r\n", file_size);
    printf("\r\n");

    char buffer[1024];
    size_t n;
    while ((n = fread(buffer, 1, sizeof(buffer), file)) > 0) {
        fwrite(buffer, 1, n, stdout);
    }
    fclose(file);
}

int main() {
    add_route("/img", img);

    // Simulate a request to /img/test.jpg
    const char *request_path = "/img";
    const char *name = "test.jpg";

    for (int i = 0; i < route_count; ++i) {
        if (strcmp(routes[i].path, request_path) == 0) {
            routes[i].handler(name);
            break;
        }
    }

    return 0;
}