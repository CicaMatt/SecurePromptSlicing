#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PATH 256

typedef struct {
    const char *path;
    void (*handler)(char *);
} Route;

Route routes[10];
int route_count = 0;

void add_route(const char *path, void (*handler)(char *)) {
    if (route_count < 10) {
        routes[route_count].path = path;
        routes[route_count].handler = handler;
        route_count++;
    }
}

void img(char *name) {
    char file_path[MAX_PATH];
    snprintf(file_path, sizeof(file_path), "images/%s", name);
    FILE *file = fopen(file_path, "rb");
    if (file == NULL) {
        printf("HTTP/1.1 404 Not Found\r\nContent-Type: text/plain\r\n\r\nFile not found.\r\n");
    } else {
        fseek(file, 0, SEEK_END);
        long file_size = ftell(file);
        rewind(file);

        printf("HTTP/1.1 200 OK\r\nContent-Type: image/jpeg\r\nContent-Length: %ld\r\n\r\n", file_size);
        fwrite(file, 1, file_size, stdout);
        fclose(file);
    }
}

void dispatch_request(const char *path, const char *query) {
    for (int i = 0; i < route_count; i++) {
        if (strcmp(routes[i].path, path) == 0) {
            routes[i].handler(query);
            return;
        }
    }
    printf("HTTP/1.1 404 Not Found\r\nContent-Type: text/plain\r\n\r\nRoute not found.\r\n");
}

int main() {
    add_route("/img", img);

    // Simulate a request
    const char *path = "/img";
    const char *query = "example.jpg";
    dispatch_request(path, query);

    return 0;
}