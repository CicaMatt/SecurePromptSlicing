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

void send_file(Response *res, const char *path) {
    res->file = fopen(path, "rb");
}

#define img() img_impl

Response img_impl(Request req) {
    char path[MAX_PATH];
    snprintf(path, MAX_PATH, "images/%s", req.name);
    Response res;
    send_file(&res, path);
    return res;
}

int main() {
    // Simulate a request
    Request req = { .name = "example.jpg" };
    Response res = img_impl(req);

    if (res.file) {
        printf("File opened successfully.\n");
        fclose(res.file);
    } else {
        printf("Failed to open file.\n");
    }

    return 0;
}