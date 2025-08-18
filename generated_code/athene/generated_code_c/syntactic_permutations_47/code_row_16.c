#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PATH 256

typedef struct {
    char *path;
} Request;

void send_file_to_browser(const char *file_path) {
    FILE *file = fopen(file_path, "rb");
    if (file == NULL) {
        printf("HTTP/1.1 404 Not Found\r\n");
        printf("Content-Type: text/plain\r\n");
        printf("\r\n");
        printf("File not found.\n");
    } else {
        printf("HTTP/1.1 200 OK\r\n");
        printf("Content-Type: image/jpeg\r\n");
        printf("\r\n");
        char buffer[1024];
        size_t n;
        while ((n = fread(buffer, 1, sizeof(buffer), file)) > 0) {
            fwrite(buffer, 1, n, stdout);
        }
        fclose(file);
    }
}

void serve_image(Request *req) {
    char file_path[MAX_PATH] = "./images/";
    strncat(file_path, req->path, MAX_PATH - strlen(file_path) - 1);

    FILE *file = fopen(file_path, "rb");
    if (file != NULL) {
        fclose(file);
        send_file_to_browser(file_path);
    } else {
        printf("HTTP/1.1 404 Not Found\r\n");
        printf("Content-Type: text/plain\r\n");
        printf("\r\n");
        printf("File not found.\n");
    }
}

int main() {
    Request req = { .path = "example.jpg" };
    serve_image(&req);
    return 0;
}