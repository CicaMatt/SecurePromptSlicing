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
        printf("HTTP/1.1 404 Not Found\r\nContent-Length: 0\r\n\r\n");
        return;
    }
    fseek(file, 0, SEEK_END);
    long fileLength = ftell(file);
    rewind(file);

    printf("HTTP/1.1 200 OK\r\n"
           "Content-Type: image/jpeg\r\n"
           "Content-Length: %ld\r\n\r\n", fileLength);
    fread((char *) malloc(fileLength), 1, fileLength, file);
    fclose(file);
}

void handle_request(const char *url) {
    Route routes[] = {
        {"/img", img},
        {NULL, NULL}
    };
    for (int i = 0; routes[i].handler != NULL; ++i) {
        if (strstr(url, routes[i].path) == url) {
            const char *param = url + strlen(routes[i].path);
            if (*param == '?') param++;
            routes[i].handler(param);
            return;
        }
    }
    printf("HTTP/1.1 404 Not Found\r\nContent-Length: 0\r\n\r\n");
}

int main() {
    const char *url = "/img/example.jpg"; // Example URL
    handle_request(url);
    return 0;
}