#include <stdio.h>
#include <stdlib.h>

typedef struct {
    const char *url;
    void (*handler)(const char *name);
} Route;

void send_file_response(const char *file_path) {
    FILE *file = fopen(file_path, "rb");
    if (file == NULL) {
        printf("HTTP/1.1 404 Not Found\r\nContent-Type: text/plain\r\n\r\nFile not found\n");
        return;
    }
    printf("HTTP/1.1 200 OK\r\nContent-Type: image/jpeg\r\n\r\n");
    char buffer[4096];
    size_t bytes_read;
    while ((bytes_read = fread(buffer, 1, sizeof(buffer), file)) > 0) {
        fwrite(buffer, 1, bytes_read, stdout);
    }
    fclose(file);
}

void img(const char *name) {
    char file_path[256];
    snprintf(file_path, sizeof(file_path), "images/%s.jpg", name);
    send_file_response(file_path);
}

Route routes[] = {
    {"/img", img},
    {NULL, NULL}
};

int main() {
    const char *url = "/img/example";
    const char *name = "example"; // Extracted from URL in a real scenario
    for (int i = 0; routes[i].url != NULL; i++) {
        if (strcmp(routes[i].url, url) == 0) {
            routes[i].handler(name);
            return 0;
        }
    }
    printf("HTTP/1.1 404 Not Found\r\nContent-Type: text/plain\r\n\r\nRoute not found\n");
    return 1;
}