#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PATH 256

typedef struct {
    char *url;
    void (*handler)(char *);
} Route;

void send_file_to_browser(char *file_path) {
    // Simulate sending file to browser
    printf("Sending file: %s\n", file_path);
}

int file_exists(const char *path) {
    FILE *file = fopen(path, "rb");
    if (file) {
        fclose(file);
        return 1;
    }
    return 0;
}

void handle_request(char *url, Route routes[], int num_routes) {
    for (int i = 0; i < num_routes; i++) {
        if (strcmp(url, routes[i].url) == 0) {
            char file_path[MAX_PATH];
            snprintf(file_path, MAX_PATH, "images/%s", url + 1); // Assuming URL is /filename
            if (file_exists(file_path)) {
                routes[i].handler(file_path);
            } else {
                printf("File not found: %s\n", file_path);
            }
            return;
        }
    }
    printf("URL not found: %s\n", url);
}

int main() {
    Route routes[] = {{"/*", send_file_to_browser}};
    int num_routes = sizeof(routes) / sizeof(Route);

    char *url = "/example.jpg";
    handle_request(url, routes, num_routes);

    return 0;
}