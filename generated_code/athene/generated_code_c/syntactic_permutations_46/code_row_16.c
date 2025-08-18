#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char *path;
} Request;

typedef struct {
    FILE *file;
} Response;

Response img(Request *request) {
    char path[256];
    snprintf(path, sizeof(path), "images/%s", request->path);
    Response response = { .file = fopen(path, "rb") };
    return response;
}

int main() {
    Request request = { .path = "example.jpg" };
    Response response = img(&request);
    if (response.file) {
        // Simulate sending the file content to a browser
        char buffer[1024];
        size_t n;
        while ((n = fread(buffer, 1, sizeof(buffer), response.file)) > 0) {
            fwrite(buffer, 1, n, stdout);
        }
        fclose(response.file);
    } else {
        fprintf(stderr, "Failed to open file\n");
        return 1;
    }
    return 0;
}