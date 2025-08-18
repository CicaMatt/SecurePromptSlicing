#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PATH 256

typedef struct {
    const char *path;
    void (*handler)(char *);
} Route;

void img(char *name) {
    char path[MAX_PATH];
    snprintf(path, sizeof(path), "images/%s", name);
    FILE *file = fopen(path, "rb");
    if (file == NULL) {
        printf("HTTP/1.1 404 Not Found\r\n"
               "Content-Type: text/plain; charset=UTF-8\r\n"
               "Content-Length: 9\r\n\r\n"
               "Not Found");
        return;
    }

    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    rewind(file);

    printf("HTTP/1.1 200 OK\r\n"
           "Content-Type: image/jpeg\r\n"
           "Content-Length: %ld\r\n\r\n", file_size);

    size_t chunk_size;
    char buffer[4096];
    while ((chunk_size = fread(buffer, 1, sizeof(buffer), file)) > 0) {
        fwrite(buffer, 1, chunk_size, stdout);
    }

    fclose(file);
}

void route_handler(const Route *route, char *param) {
    if (strcmp(route->path, "/img") == 0) {
        route->handler(param);
    }
}

int main() {
    const Route routes[] = {
        {"/img", img},
    };

    // Simulate a request
    char param[] = "example.jpg";
    route_handler(routes, param);

    return 0;
}