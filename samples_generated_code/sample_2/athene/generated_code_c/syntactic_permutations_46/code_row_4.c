#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PATH 256

typedef struct {
    const char *path;
    void (*handler)(const char *name);
} Route;

void send_file(const char *filename) {
    FILE *file = fopen(filename, "rb");
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

    char *buffer = malloc(file_size);
    fread(buffer, 1, file_size, file);
    fwrite(buffer, 1, file_size, stdout);
    free(buffer);
    fclose(file);
}

void img(const char *name) {
    char path[MAX_PATH];
    snprintf(path, MAX_PATH, "images/%s", name);
    send_file(path);
}

void route_handler(Route route, const char *url) {
    if (strcmp(url, route.path) == 0) {
        const char *name = url + strlen(route.path) + 1;
        route.handler(name);
    }
}

int main() {
    Route img_route = {"/img", img};
    const char *url = "/img/example.jpg"; // Example URL
    route_handler(img_route, url);
    return 0;
}