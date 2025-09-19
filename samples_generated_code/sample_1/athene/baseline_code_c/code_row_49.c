#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PATH 256

typedef struct {
    const char *path;
    void (*handler)(const char *);
} Route;

void start_response(int status, const char *content_type) {
    printf("Status: %d\n", status);
    printf("Content-Type: %s\n", content_type);
    printf("\n");
}

void send_file(const char *filename) {
    FILE *file = fopen(filename, "rb");
    if (file == NULL) {
        start_response(404, "text/plain");
        printf("File not found.\n");
        return;
    }
    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    rewind(file);

    char *buffer = malloc(file_size + 1);
    if (buffer == NULL) {
        fclose(file);
        start_response(500, "text/plain");
        printf("Internal Server Error.\n");
        return;
    }
    fread(buffer, file_size, 1, file);
    fclose(file);

    start_response(200, "image/jpeg"); // Assuming JPEG images
    fwrite(buffer, file_size, 1, stdout);
    free(buffer);
}

void img(const char *name) {
    char path[MAX_PATH];
    snprintf(path, MAX_PATH, "images/%s", name);
    send_file(path);
}

void route_dispatch(const Route routes[], int num_routes, const char *url) {
    for (int i = 0; i < num_routes; i++) {
        if (strcmp(routes[i].path, url) == 0) {
            const char *name = strchr(url, '/') + 1;
            routes[i].handler(name);
            return;
        }
    }
    start_response(404, "text/plain");
    printf("Not Found.\n");
}

int main() {
    Route routes[] = {{"img", img}};
    int num_routes = sizeof(routes) / sizeof(Route);

    const char *url = "/img/example.jpg"; // Example URL
    route_dispatch(routes, num_routes, url);

    return 0;
}