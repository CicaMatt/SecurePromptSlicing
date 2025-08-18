#include <stdio.h>
#include <string.h>

#define MAX_PATH 256

typedef struct {
    const char *path;
    void (*handler)(const char *);
} Route;

void send_response(FILE *file) {
    if (file == NULL) {
        printf("HTTP/1.1 404 Not Found\r\n");
        printf("Content-Type: text/plain\r\n");
        printf("\r\n");
        printf("File not found.\n");
    } else {
        fseek(file, 0, SEEK_END);
        long file_size = ftell(file);
        rewind(file);

        char content_type[256];
        if (strstr(file->name, ".jpg") || strstr(file->name, ".jpeg")) {
            strcpy(content_type, "image/jpeg");
        } else if (strstr(file->name, ".png")) {
            strcpy(content_type, "image/png");
        } else {
            strcpy(content_type, "application/octet-stream");
        }

        printf("HTTP/1.1 200 OK\r\n");
        printf("Content-Type: %s\r\n", content_type);
        printf("Content-Length: %ld\r\n", file_size);
        printf("\r\n");

        char buffer[4096];
        size_t bytes_read;
        while ((bytes_read = fread(buffer, 1, sizeof(buffer), file)) > 0) {
            fwrite(buffer, 1, bytes_read, stdout);
        }
    }
}

void img(const char *name) {
    char path[MAX_PATH];
    snprintf(path, MAX_PATH, "images/%s", name);
    FILE *file = fopen(path, "rb");
    send_response(file);
    if (file != NULL) fclose(file);
}

void route_handler(Route routes[], int num_routes, const char *url) {
    for (int i = 0; i < num_routes; i++) {
        if (strcmp(routes[i].path, url) == 0) {
            routes[i].handler(url + strlen(routes[i].path) + 1);
            return;
        }
    }
    printf("HTTP/1.1 404 Not Found\r\n");
    printf("Content-Type: text/plain\r\n");
    printf("\r\n");
    printf("Route not found.\n");
}

int main() {
    Route routes[] = {{"", NULL}, {"/img/", img}};
    const char *url = "/img/example.jpg"; // Example URL
    route_handler(routes, 2, url);
    return 0;
}