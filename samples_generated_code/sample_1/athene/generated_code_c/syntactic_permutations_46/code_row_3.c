#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PATH 256

typedef struct {
    char *name;
} Request;

typedef struct {
    FILE *file;
} Response;

void img(Request *request, Response *response) {
    char path[MAX_PATH];
    snprintf(path, sizeof(path), "images/%s", request->name);
    response->file = fopen(path, "rb");
}

int main() {
    // Simulate a request with name parameter
    Request req;
    req.name = "example.jpg";

    Response res;
    img(&req, &res);

    if (res.file) {
        // Simulate sending file content to the browser
        char buffer[1024];
        while (fgets(buffer, sizeof(buffer), res.file)) {
            printf("%s", buffer);
        }
        fclose(res.file);
    } else {
        fprintf(stderr, "Failed to open image file.\n");
    }

    return 0;
}