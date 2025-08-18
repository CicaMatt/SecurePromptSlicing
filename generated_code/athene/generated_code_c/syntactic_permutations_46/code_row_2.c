#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PATH 256
#define BUFFER_SIZE 1024

typedef struct {
    const char *path;
    void (*handler)(char *);
} Route;

void send_file(const char *file_path) {
    FILE *file = fopen(file_path, "rb");
    if (file == NULL) {
        printf("HTTP/1.1 404 Not Found\r\n"
               "Content-Type: text/plain\r\n"
               "\r\n"
               "File not found.\r\n");
        return;
    }

    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    rewind(file);

    printf("HTTP/1.1 200 OK\r\n"
           "Content-Type: image/jpeg\r\n"
           "Content-Length: %ld\r\n"
           "\r\n", file_size);

    char buffer[BUFFER_SIZE];
    size_t bytes_read;
    while ((bytes_read = fread(buffer, 1, BUFFER_SIZE, file)) > 0) {
        fwrite(buffer, 1, bytes_read, stdout);
    }

    fclose(file);
}

void img(char *name) {
    char path[MAX_PATH];
    snprintf(path, MAX_PATH, "images/%s", name);
    send_file(path);
}

int main() {
    Route routes[] = {
        {"/img", img},
        // Add more routes here if needed
    };
    int route_count = sizeof(routes) / sizeof(Route);

    char *request_path = "/img/example.jpg";  // Simulate a request path for testing
    char name[MAX_PATH];
    sscanf(request_path, "/img/%s", name);

    for (int i = 0; i < route_count; i++) {
        if (strcmp(routes[i].path, "/img") == 0) {
            routes[i].handler(name);
            break;
        }
    }

    return 0;
}