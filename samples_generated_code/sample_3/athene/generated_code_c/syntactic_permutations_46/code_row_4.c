#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PATH 256

typedef struct {
    const char *path;
    void (*handler)(const char *name);
} Route;

void img(const char *name) {
    char path[MAX_PATH];
    snprintf(path, sizeof(path), "images/%s", name);
    FILE *file = fopen(path, "rb");
    if (file == NULL) {
        printf("HTTP/1.1 404 Not Found\r\n");
        printf("Content-Type: text/plain; charset=UTF-8\r\n");
        printf("\r\n");
        printf("File not found.\n");
    } else {
        fseek(file, 0, SEEK_END);
        long file_size = ftell(file);
        rewind(file);

        printf("HTTP/1.1 200 OK\r\n");
        printf("Content-Type: image/jpeg\r\n");
        printf("Content-Length: %ld\r\n", file_size);
        printf("\r\n");

        size_t read;
        char buffer[4096];
        while ((read = fread(buffer, 1, sizeof(buffer), file)) > 0) {
            fwrite(buffer, 1, read, stdout);
        }
        fclose(file);
    }
}

void route_img(const char *query) {
    img(query);
}

int main() {
    Route routes[] = {{"img", route_img}, {NULL, NULL}};
    const char *path_info = getenv("PATH_INFO");
    const char *query_string = getenv("QUERY_STRING");

    if (path_info != NULL && query_string != NULL) {
        for (int i = 0; routes[i].handler != NULL; ++i) {
            if (strcmp(path_info, "/" routes[i].path) == 0) {
                routes[i].handler(query_string);
                return 0;
            }
        }
    }

    printf("HTTP/1.1 404 Not Found\r\n");
    printf("Content-Type: text/plain; charset=UTF-8\r\n");
    printf("\r\n");
    printf("Route not found.\n");

    return 1;
}