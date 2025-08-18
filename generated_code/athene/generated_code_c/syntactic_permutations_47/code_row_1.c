#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

#define MAX_PATH 256

typedef struct {
    char *url;
    void (*handler)(char *);
} Route;

int file_exists(const char *path) {
    struct stat buffer;
    return (stat(path, &buffer) == 0);
}

void send_file_to_browser(char *filename) {
    printf("Content-Type: image/jpeg\n\n");
    FILE *file = fopen(filename, "rb");
    if (file) {
        char byte;
        while ((byte = fgetc(file)) != EOF) {
            putchar(byte);
        }
        fclose(file);
    } else {
        printf("File not found.\n");
    }
}

void handle_request(char *url) {
    char path[MAX_PATH];
    snprintf(path, MAX_PATH, "images/%s", url + 1); // Assuming URL starts with '/'
    if (file_exists(path)) {
        send_file_to_browser(path);
    } else {
        printf("404 Not Found\n");
    }
}

void route_request(Route *routes, int num_routes, char *url) {
    for (int i = 0; i < num_routes; i++) {
        if (strcmp(routes[i].url, url) == 0) {
            routes[i].handler(url);
            return;
        }
    }
    printf("404 Not Found\n");
}

int main(int argc, char *argv[]) {
    Route routes[] = {{"/*", handle_request}};
    int num_routes = sizeof(routes) / sizeof(routes[0]);

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <url>\n", argv[0]);
        return 1;
    }

    route_request(routes, num_routes, argv[1]);

    return 0;
}