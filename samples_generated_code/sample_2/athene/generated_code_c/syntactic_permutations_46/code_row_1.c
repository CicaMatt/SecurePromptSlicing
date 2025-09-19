#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    const char *url;
    void (*handler)(const char *);
} Route;

void img(const char *name) {
    FILE *file = fopen(name, "rb");
    if (file == NULL) {
        printf("Content-Type: text/plain\r\n");
        printf("Status: 404 Not Found\r\n\r\n");
        printf("File not found.\n");
    } else {
        printf("Content-Type: image/jpeg\r\n\r\n");
        char buffer[1024];
        size_t bytesRead;
        while ((bytesRead = fread(buffer, 1, sizeof(buffer), file)) > 0) {
            fwrite(buffer, 1, bytesRead, stdout);
        }
        fclose(file);
    }
}

void route_handler(const Route *routes, int count, const char *path) {
    for (int i = 0; i < count; i++) {
        if (strcmp(routes[i].url, path) == 0) {
            routes[i].handler(path + strlen(routes[i].url));
            return;
        }
    }
    printf("Content-Type: text/plain\r\n");
    printf("Status: 404 Not Found\r\n\r\n");
    printf("Route not found.\n");
}

int main() {
    Route routes[] = {{"img/", img}};
    const int route_count = sizeof(routes) / sizeof(routes[0]);

    char *path_info = getenv("PATH_INFO");
    if (path_info != NULL && path_info[0] == '/') {
        path_info++;
    }

    route_handler(routes, route_count, path_info ? path_info : "");

    return 0;
}