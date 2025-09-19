#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PATH 256

typedef struct {
    const char *url;
    void (*handler)(const char *);
} route_t;

void img(const char *name) {
    char path[MAX_PATH];
    snprintf(path, sizeof(path), "images/%s", name);
    FILE *file = fopen(path, "rb");
    if (file == NULL) {
        printf("HTTP/1.1 404 Not Found\r\nContent-Type: text/plain\r\n\r\nFile not found.\r\n");
        return;
    }
    fseek(file, 0, SEEK_END);
    long size = ftell(file);
    rewind(file);

    printf("HTTP/1.1 200 OK\r\nContent-Type: image/jpeg\r\nContent-Length: %ld\r\n\r\n", size);
    char buffer[1024];
    while (size > 0) {
        size_t to_read = size < sizeof(buffer) ? size : sizeof(buffer);
        fread(buffer, 1, to_read, file);
        fwrite(buffer, 1, to_read, stdout);
        size -= to_read;
    }
    fclose(file);
}

void route_dispatch(const route_t routes[], const char *url, const char *name) {
    for (int i = 0; routes[i].url != NULL; ++i) {
        if (strcmp(routes[i].url, url) == 0) {
            routes[i].handler(name);
            return;
        }
    }
    printf("HTTP/1.1 404 Not Found\r\nContent-Type: text/plain\r\n\r\nRoute not found.\r\n");
}

int main() {
    route_t routes[] = {
        {"/img", img},
        {NULL, NULL}
    };

    const char *url = "/img";
    const char *name = "example.jpg"; // Example name parameter
    route_dispatch(routes, url, name);

    return 0;
}