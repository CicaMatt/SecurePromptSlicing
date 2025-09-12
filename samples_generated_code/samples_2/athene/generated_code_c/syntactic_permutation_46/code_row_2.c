#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PATH 256

typedef struct {
    char *url;
    void (*handler)(char *);
} Route;

Route routes[10];
int route_count = 0;

void add_route(const char *url, void (*handler)(char *)) {
    if (route_count < 10) {
        routes[route_count].url = strdup(url);
        routes[route_count].handler = handler;
        route_count++;
    }
}

void img(char *name) {
    char path[MAX_PATH];
    snprintf(path, MAX_PATH, "images/%s", name);
    FILE *file = fopen(path, "rb");
    if (file) {
        // Simulate sending file content to browser
        char buffer[1024];
        while (fread(buffer, 1, sizeof(buffer), file)) {
            fwrite(buffer, 1, sizeof(buffer), stdout);
        }
        fclose(file);
    } else {
        fprintf(stderr, "File not found: %s\n", path);
    }
}

void handle_request(const char *url, const char *param) {
    for (int i = 0; i < route_count; i++) {
        if (strcmp(routes[i].url, url) == 0) {
            routes[i].handler(param);
            return;
        }
    }
    printf("404 Not Found\n");
}

int main() {
    add_route("/img", img);

    // Simulate a request
    handle_request("/img", "example.jpg");

    return 0;
}