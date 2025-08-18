#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PATH 256

typedef struct {
    const char *url;
    void (*handler)(const char *);
} Route;

void img(const char *name) {
    char path[MAX_PATH];
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
    char buffer[1024];
    size_t n;
    while ((n = fread(buffer, 1, sizeof(buffer), file)) > 0) {
        fwrite(buffer, 1, n, stdout);
    }
    fclose(file);
}

void route_img(const char *name) {
    img(name);
}

Route routes[] = {
    {"/img", route_img},
    {NULL, NULL}
};

int main() {
    const char *url = "/img";
    const char *param = "example.jpg"; // Example parameter
    for (int i = 0; routes[i].url != NULL; i++) {
        if (strcmp(routes[i].url, url) == 0) {
            routes[i].handler(param);
            break;
        }
    }
    return 0;
}