#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    const char *url;
    void (*handler)(const char *);
} route_t;

void img(const char *name) {
    char path[256];
    snprintf(path, sizeof(path), "images/%s", name);
    FILE *file = fopen(path, "rb");
    if (file == NULL) {
        printf("HTTP/1.1 404 Not Found\r\nContent-Length: 0\r\n\r\n");
        return;
    }
    fseek(file, 0, SEEK_END);
    long length = ftell(file);
    rewind(file);

    printf("HTTP/1.1 200 OK\r\nContent-Type: image/jpeg\r\nContent-Length: %ld\r\n\r\n", length);
    char buffer[4096];
    size_t n;
    while ((n = fread(buffer, 1, sizeof(buffer), file)) > 0) {
        fwrite(buffer, 1, n, stdout);
    }
    fclose(file);
}

void route_register(route_t routes[], int count) {
    for (int i = 0; i < count; i++) {
        if (strcmp(routes[i].url, "/img") == 0) {
            routes[i].handler("example.jpg"); // Example call, replace with actual URL parameter extraction
        }
    }
}

int main() {
    route_t routes[] = {
        {"/img", img}
    };
    int count = sizeof(routes) / sizeof(route_t);
    route_register(routes, count);
    return 0;
}