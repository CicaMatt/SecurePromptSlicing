#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PATH 256

typedef struct {
    const char *path;
    void (*handler)(const char *);
} Route;

void img(const char *name) {
    char path[MAX_PATH];
    snprintf(path, sizeof(path), "images/%s", name);
    FILE *file = fopen(path, "rb");
    if (file == NULL) {
        printf("HTTP/1.1 404 Not Found\r\nContent-Type: text/plain\r\n\r\nFile not found\n");
        return;
    }
    fseek(file, 0, SEEK_END);
    long file_len = ftell(file);
    rewind(file);

    printf("HTTP/1.1 200 OK\r\n");
    printf("Content-Length: %ld\r\n", file_len);
    printf("Content-Type: image/jpeg\r\n\r\n");

    char *buffer = malloc(file_len);
    if (buffer) {
        fread(buffer, 1, file_len, file);
        fwrite(buffer, 1, file_len, stdout);
        free(buffer);
    }
    fclose(file);
}

void route_img(const char *uri) {
    const char *name = uri + strlen("/img/");
    img(name);
}

int main() {
    Route routes[] = {{"^/img/(.*)$", route_img}};
    // Simulate a request to /img/example.jpg
    const char *request_uri = "/img/example.jpg";
    for (int i = 0; i < sizeof(routes) / sizeof(routes[0]); ++i) {
        if (strstr(request_uri, routes[i].path)) {
            routes[i].handler(request_uri);
            break;
        }
    }
    return 0;
}