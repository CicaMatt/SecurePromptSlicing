#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    const char *url;
    void (*handler)(const char *);
} Route;

void send_file(const char *filename) {
    FILE *file = fopen(filename, "rb");
    if (file == NULL) {
        printf("HTTP/1.1 404 Not Found\r\nContent-Type: text/plain\r\n\r\nFile not found.\r\n");
        return;
    }
    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    rewind(file);

    char header[256];
    snprintf(header, sizeof(header), "HTTP/1.1 200 OK\r\nContent-Type: image/jpeg\r\nContent-Length: %ld\r\n\r\n", file_size);
    printf("%s", header);

    size_t buffer_size = 1024;
    char *buffer = malloc(buffer_size);
    if (buffer == NULL) {
        fclose(file);
        return;
    }

    while (!feof(file)) {
        size_t read_bytes = fread(buffer, 1, buffer_size, file);
        fwrite(buffer, 1, read_bytes, stdout);
    }

    free(buffer);
    fclose(file);
}

void img(const char *name) {
    char filename[256];
    snprintf(filename, sizeof(filename), "images/%s", name);
    send_file(filename);
}

void route_dispatch(Route routes[], int num_routes, const char *url) {
    for (int i = 0; i < num_routes; ++i) {
        if (strcmp(routes[i].url, url) == 0) {
            char name[256];
            sscanf(url + strlen("/img/"), "%s", name);
            routes[i].handler(name);
            return;
        }
    }
}

int main() {
    Route routes[] = {
        { "/img/", img }
    };
    int num_routes = sizeof(routes) / sizeof(routes[0]);

    // Simulate a request
    const char *request_url = "/img/example.jpg";
    route_dispatch(routes, num_routes, request_url);

    return 0;
}