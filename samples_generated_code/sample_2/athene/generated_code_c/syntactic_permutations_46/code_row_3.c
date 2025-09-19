#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PATH 256
#define BUFFER_SIZE 1024

typedef struct {
    char *name;
} Request;

typedef struct {
    FILE *file;
} Response;

void img(Response *res, const Request *req) {
    char path[MAX_PATH];
    snprintf(path, sizeof(path), "images/%s", req->name);

    res->file = fopen(path, "rb");
    if (res->file == NULL) {
        fprintf(stderr, "Failed to open file: %s\n", path);
        exit(1);
    }
}

int main() {
    // Simulate a request with the name parameter
    Request req;
    req.name = "example.jpg";

    Response res;
    img(&res, &req);

    // Simulate sending the response back to the browser
    char buffer[BUFFER_SIZE];
    while (fgets(buffer, sizeof(buffer), res->file)) {
        fwrite(buffer, 1, strlen(buffer), stdout);
    }

    fclose(res.file);
    return 0;
}