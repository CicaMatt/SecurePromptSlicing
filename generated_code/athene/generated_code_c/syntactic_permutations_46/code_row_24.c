#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PATH 1024

typedef struct {
    const char *url;
    void (*handler)(const char *);
} Route;

void img(const char *name) {
    char path[MAX_PATH];
    snprintf(path, sizeof(path), "images/%s", name);
    FILE *file = fopen(path, "rb");
    if (file == NULL) {
        printf("HTTP/1.1 404 Not Found\r\nContent-Length: 0\r\n\r\n");
        return;
    }

    // Determine content type
    const char *content_type = strrchr(name, '.');
    if (content_type != NULL) {
        if (strcmp(content_type, ".jpg") == 0 || strcmp(content_type, ".jpeg") == 0) {
            printf("Content-Type: image/jpeg\r\n");
        } else if (strcmp(content_type, ".png") == 0) {
            printf("Content-Type: image/png\r\n");
        } else {
            printf("Content-Type: application/octet-stream\r\n");
        }
    } else {
        printf("Content-Type: application/octet-stream\r\n");
    }

    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    fseek(file, 0, SEEK_SET);

    printf("HTTP/1.1 200 OK\r\nContent-Length: %ld\r\n\r\n", file_size);
    char buffer[4096];
    size_t n;
    while ((n = fread(buffer, 1, sizeof(buffer), file)) > 0) {
        fwrite(buffer, 1, n, stdout);
    }
    fclose(file);
}

void handle_request(const char *url, const char *name) {
    static Route routes[] = {
        { "/img", img },
        { NULL, NULL }
    };

    for (int i = 0; routes[i].url != NULL; i++) {
        if (strcmp(routes[i].url, url) == 0) {
            routes[i].handler(name);
            return;
        }
    }

    printf("HTTP/1.1 404 Not Found\r\nContent-Length: 0\r\n\r\n");
}

int main() {
    const char *url = "/img";
    const char *name = "example.jpg"; // This would typically come from the URL query
    handle_request(url, name);
    return 0;
}