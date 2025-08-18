#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    const char *url;
    void (*handler)(const char *name);
} Route;

Route routes[10];
int route_count = 0;

void add_route(const char *url, void (*handler)(const char *name)) {
    if (route_count < 10) {
        routes[route_count].url = url;
        routes[route_count].handler = handler;
        route_count++;
    }
}

void img(const char *name) {
    FILE *file = fopen(strcat("images/", name), "rb");
    if (file == NULL) {
        printf("File not found\n");
        return;
    }

    // Simulate sending file content as response
    char buffer[1024];
    while (fread(buffer, 1, sizeof(buffer), file)) {
        fwrite(buffer, 1, sizeof(buffer), stdout);
    }
    fclose(file);
}

int main() {
    add_route("/img", img);

    // Simulate a request to /img?name=example.png
    const char *request_url = "/img";
    const char *name_param = "example.png";

    for (int i = 0; i < route_count; i++) {
        if (strcmp(routes[i].url, request_url) == 0) {
            routes[i].handler(name_param);
            break;
        }
    }

    return 0;
}