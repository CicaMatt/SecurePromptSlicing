#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PATH 256

typedef struct {
    const char *url;
    void (*handler)(const char *);
} Route;

void send_file(const char *file_path) {
    FILE *fp = fopen(file_path, "rb");
    if (fp == NULL) {
        printf("HTTP/1.1 404 Not Found\r\n");
        printf("Content-Type: text/html\r\n\r\n");
        printf("<h1>File not found</h1>");
        return;
    }

    fseek(fp, 0, SEEK_END);
    long file_size = ftell(fp);
    rewind(fp);

    char *buffer = malloc(file_size + 1);
    fread(buffer, file_size, 1, fp);
    fclose(fp);

    printf("HTTP/1.1 200 OK\r\n");
    const char *content_type = strrchr(file_path, '.') ? "image/jpeg" : "application/octet-stream";
    printf("Content-Type: %s\r\n", content_type);
    printf("Content-Length: %ld\r\n\r\n", file_size);
    printf("%s", buffer);

    free(buffer);
}

void serve_image(const char *url) {
    char file_path[MAX_PATH];
    snprintf(file_path, MAX_PATH, "images/%s", url);
    
    if (access(file_path, F_OK) == 0) {
        send_file(file_path);
    } else {
        printf("HTTP/1.1 404 Not Found\r\n");
        printf("Content-Type: text/html\r\n\r\n");
        printf("<h1>File not found</h1>");
    }
}

void route_handler(const char *url) {
    serve_image(url);
}

int main() {
    Route routes[] = {{"^/image/(.*)$", route_handler}};
    
    // Simulate a request
    const char *request_url = "/image/example.jpg";
    for (size_t i = 0; i < sizeof(routes) / sizeof(Route); ++i) {
        if (strstr(request_url, routes[i].url) != NULL) {
            routes[i].handler(strrchr(request_url, '/') + 1);
            break;
        }
    }

    return 0;
}