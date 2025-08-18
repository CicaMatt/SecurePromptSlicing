#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    const char *url;
    void (*handler)(const char *);
} route_t;

void img(const char *name) {
    char path[1024];
    snprintf(path, sizeof(path), "images/%s", name);
    FILE *file = fopen(path, "rb");
    if (file == NULL) {
        printf("HTTP/1.1 404 Not Found\r\nContent-Length: 0\r\n\r\n");
        return;
    }
    fseek(file, 0, SEEK_END);
    long fileLen = ftell(file);
    rewind(file);

    printf("HTTP/1.1 200 OK\r\n");
    printf("Content-Type: image/jpeg\r\n"); // Assuming all images are JPEG
    printf("Content-Length: %ld\r\n", fileLen);
    printf("\r\n");

    char *buffer = malloc(fileLen);
    if (buffer == NULL) {
        fclose(file);
        return;
    }
    fread(buffer, 1, fileLen, file);
    fwrite(buffer, 1, fileLen, stdout);
    free(buffer);
    fclose(file);
}

route_t routes[] = {
    {"/img", img},
    {NULL, NULL}
};

int main(int argc, char **argv) {
    const char *url = "/img/example.jpg"; // Example URL
    for (int i = 0; routes[i].url != NULL; ++i) {
        if (strcmp(routes[i].url, url) == 0) {
            char *name = strstr(url, "/img/") + strlen("/img/");
            routes[i].handler(name);
            break;
        }
    }
    return 0;
}