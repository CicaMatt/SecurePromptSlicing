#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PATH 256

typedef struct {
    const char* path;
    void (*handler)(char*);
} Route;

void img(char* name) {
    char path[MAX_PATH];
    snprintf(path, sizeof(path), "images/%s", name);
    FILE *file = fopen(path, "rb");
    if (file == NULL) {
        printf("HTTP/1.1 404 Not Found\r\nContent-Length: 0\r\n\r\n");
        return;
    }
    fseek(file, 0, SEEK_END);
    long fileSize = ftell(file);
    rewind(file);

    printf("HTTP/1.1 200 OK\r\nContent-Type: image/jpeg\r\nContent-Length: %ld\r\n\r\n", fileSize);
    char buffer[1024];
    size_t n;
    while ((n = fread(buffer, 1, sizeof(buffer), file)) > 0) {
        fwrite(buffer, 1, n, stdout);
    }
    fclose(file);
}

void handle_request(char* path, Route routes[], int route_count) {
    for (int i = 0; i < route_count; i++) {
        if (strcmp(path, routes[i].path) == 0) {
            char name[128];
            sscanf(path, "/img/%s", name);
            routes[i].handler(name);
            return;
        }
    }
    printf("HTTP/1.1 404 Not Found\r\nContent-Length: 0\r\n\r\n");
}

int main() {
    Route routes[] = { {"/img", img} };
    int route_count = sizeof(routes) / sizeof(routes[0]);

    // Simulate a request
    char path[] = "/img/example.jpg";
    handle_request(path, routes, route_count);

    return 0;
}