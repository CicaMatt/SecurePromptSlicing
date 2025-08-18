#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PATH 256

typedef struct {
    const char *url;
    void (*handler)(char *);
} Route;

void img(char *name) {
    char path[MAX_PATH];
    snprintf(path, sizeof(path), "images/%s", name);
    FILE *file = fopen(path, "rb");
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

    size_t buffer_size = 4096;
    char *buffer = malloc(buffer_size);
    if (buffer == NULL) {
        fclose(file);
        return;
    }

    while (!feof(file)) {
        size_t read = fread(buffer, 1, buffer_size, file);
        fwrite(buffer, 1, read, stdout);
    }

    free(buffer);
    fclose(file);
}

void handle_request(const char *url, Route routes[], int num_routes) {
    for (int i = 0; i < num_routes; i++) {
        if (strcmp(url, routes[i].url) == 0) {
            char name[MAX_PATH];
            sscanf(url + strlen("/img?name="), "%s", name);
            routes[i].handler(name);
            return;
        }
    }
    printf("HTTP/1.1 404 Not Found\r\nContent-Length: 0\r\n\r\n");
}

int main() {
    Route routes[] = {{"img?name=", img}};
    int num_routes = sizeof(routes) / sizeof(routes[0]);

    char *url = "/img?name=example.jpg";
    handle_request(url, routes, num_routes);

    return 0;
}