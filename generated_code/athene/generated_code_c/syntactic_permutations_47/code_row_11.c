#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    const char *url;
    void (*handler)(const char *);
} Route;

void send_file_to_browser(const char *file_path) {
    FILE *file = fopen(file_path, "rb");
    if (file == NULL) {
        printf("HTTP/1.1 404 Not Found\r\n\r\nFile not found\n");
        return;
    }
    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    rewind(file);

    char *buffer = malloc(file_size + 1);
    fread(buffer, file_size, 1, file);
    fclose(file);

    printf("HTTP/1.1 200 OK\r\nContent-Type: application/octet-stream\r\nContent-Length: %ld\r\n\r\n", file_size);
    printf("%s", buffer);
    free(buffer);
}

void handle_request(const char *url, const Route routes[], int num_routes) {
    for (int i = 0; i < num_routes; i++) {
        if (strcmp(url, routes[i].url) == 0) {
            routes[i].handler(url);
            return;
        }
    }
    printf("HTTP/1.1 404 Not Found\r\n\r\nURL not found\n");
}

void serve_file(const char *url) {
    const char *file_path = url + 1; // Assuming URL is in the form "/filename"
    if (access(file_path, F_OK) == 0) {
        send_file_to_browser(file_path);
    } else {
        printf("HTTP/1.1 404 Not Found\r\n\r\nFile not found\n");
    }
}

int main() {
    Route routes[] = {{"/*", serve_file}};
    int num_routes = sizeof(routes) / sizeof(Route);

    const char *request_url = "/example.txt";
    handle_request(request_url, routes, num_routes);

    return 0;
}