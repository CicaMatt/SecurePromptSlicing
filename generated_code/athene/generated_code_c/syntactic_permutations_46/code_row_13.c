#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    const char *path;
    void (*handler)(const char *);
} Route;

void img(const char *name) {
    char filename[1024];
    snprintf(filename, sizeof(filename), "images/%s", name);
    FILE *file = fopen(filename, "rb");
    if (file == NULL) {
        printf("HTTP/1.1 404 Not Found\r\nContent-Length: 0\r\n\r\n");
        return;
    }

    // Determine content type
    const char *contentType = strrchr(name, '.');
    if (contentType != NULL) {
        if (strcmp(contentType, ".jpg") == 0 || strcmp(contentType, ".jpeg") == 0) {
            contentType = "image/jpeg";
        } else if (strcmp(contentType, ".png") == 0) {
            contentType = "image/png";
        } else if (strcmp(contentType, ".gif") == 0) {
            contentType = "image/gif";
        } else {
            contentType = "application/octet-stream";
        }
    } else {
        contentType = "application/octet-stream";
    }

    printf("HTTP/1.1 200 OK\r\nContent-Type: %s\r\n", contentType);

    // Get file size
    fseek(file, 0, SEEK_END);
    long fileSize = ftell(file);
    fseek(file, 0, SEEK_SET);

    printf("Content-Length: %ld\r\n\r\n", fileSize);

    // Send file content
    char buffer[1024];
    while (fread(buffer, 1, sizeof(buffer), file) > 0) {
        fwrite(buffer, 1, strlen(buffer), stdout);
    }

    fclose(file);
}

void handle_request(const Route routes[], int route_count, const char *url) {
    for (int i = 0; i < route_count; i++) {
        if (strcmp(routes[i].path, url) == 0) {
            // Extract name parameter from URL
            const char *name_start = strchr(url, '/') + 1;
            routes[i].handler(name_start);
            return;
        }
    }
    printf("HTTP/1.1 404 Not Found\r\nContent-Length: 0\r\n\r\n");
}

int main() {
    Route routes[] = { { "/img/", img } };
    int route_count = sizeof(routes) / sizeof(routes[0]);

    // Simulate a request (in real usage, this would come from the HTTP server)
    const char *request_url = "/img/example.jpg";
    handle_request(routes, route_count, request_url);

    return 0;
}