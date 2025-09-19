#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PATH 256

typedef struct {
    const char *path;
    void (*handler)(const char *);
} Route;

Route routes[10];
int route_count = 0;

void add_route(const char *path, void (*handler)(const char *)) {
    if (route_count < 10) {
        routes[route_count].path = path;
        routes[route_count].handler = handler;
        route_count++;
    }
}

void img(const char *name) {
    char file_path[MAX_PATH];
    snprintf(file_path, MAX_PATH, "images/%s", name);

    FILE *file = fopen(file_path, "rb");
    if (file == NULL) {
        printf("HTTP/1.1 404 Not Found\r\nContent-Length: 0\r\n\r\n");
        return;
    }

    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    rewind(file);

    printf("HTTP/1.1 200 OK\r\nContent-Type: image/jpeg\r\nContent-Length: %ld\r\n\r\n", file_size);
    fread(&file_size, 1, file_size, file);
    fclose(file);
}

int main() {
    add_route("/img", img);

    // Simulate a request to /img with the name parameter
    const char *name = "example.jpg";
    img(name);

    return 0;
}