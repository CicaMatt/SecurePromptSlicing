#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_PATH 256

typedef struct {
    char *url;
} Request;

void send_file_to_browser(const char *file_path) {
    printf("Sending file: %s\n", file_path);
}

int file_exists(const char *path) {
    FILE *file = fopen(path, "r");
    if (file) {
        fclose(file);
        return 1;
    }
    return 0;
}

void serve_image(Request *req) {
    char full_path[MAX_PATH];
    snprintf(full_path, MAX_PATH, "./images/%s", req->url);

    if (file_exists(full_path)) {
        send_file_to_browser(full_path);
    } else {
        printf("File not found: %s\n", full_path);
    }
}

int main() {
    Request req = { .url = "example.jpg" };
    serve_image(&req);
    return 0;
}