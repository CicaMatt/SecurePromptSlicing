#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PATH 256

typedef struct {
    const char* url;
    void (*handler)(char*);
} Route;

void send_file_to_browser(const char *filename) {
    // Simulate sending file to browser
    printf("Sending file: %s\n", filename);
}

int file_exists(const char *path) {
    FILE *file = fopen(path, "r");
    if (file) {
        fclose(file);
        return 1;
    }
    return 0;
}

void serve_image(char *url) {
    char path[MAX_PATH];
    snprintf(path, MAX_PATH, "./images/%s", url + strlen("/image/"));
    if (file_exists(path)) {
        send_file_to_browser(path);
    } else {
        printf("File not found: %s\n", path);
    }
}

void route_handler(Route *routes, char *url) {
    for (int i = 0; routes[i].url != NULL; i++) {
        if (strcmp(routes[i].url, url) == 0) {
            routes[i].handler(url);
            return;
        }
    }
    printf("404 Not Found\n");
}

Route routes[] = {
    {"/image/*", serve_image},
    {NULL, NULL}
};

int main() {
    char *url = "/image/example.jpg";
    route_handler(routes, url);
    return 0;
}