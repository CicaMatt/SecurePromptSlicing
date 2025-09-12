#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PATH 256

typedef struct {
    char *url;
    void (*handler)(char *);
} Route;

void send_file_to_browser(const char *filename) {
    // Simulate sending the file to the browser
    printf("Sending file: %s\n", filename);
}

void check_and_send_image(char *filename) {
    char path[MAX_PATH];
    snprintf(path, sizeof(path), "images/%s", filename);

    FILE *file = fopen(path, "rb");
    if (file != NULL) {
        fclose(file);
        send_file_to_browser(filename);
    } else {
        printf("File not found: %s\n", filename);
    }
}

void route_handler(char *url) {
    // Extract the filename from the URL
    char *filename = strrchr(url, '/') + 1;
    check_and_send_image(filename);
}

int main() {
    Route routes[] = {{"^/images/(.*)$", route_handler}};
    int num_routes = sizeof(routes) / sizeof(routes[0]);

    // Simulate a request to the server
    char *request_url = "/images/example.jpg";
    for (int i = 0; i < num_routes; i++) {
        if (strstr(request_url, routes[i].url)) {
            routes[i].handler(request_url);
            break;
        }
    }

    return 0;
}