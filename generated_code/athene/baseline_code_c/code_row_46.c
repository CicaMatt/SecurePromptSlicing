#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *name;
} Request;

typedef struct {
    FILE *file;
} Response;

typedef void (*Handler)(Request, Response *);

void send_file(Response *res, const char *filename) {
    res->file = fopen(filename, "rb");
}

#define URL_DECORATOR(fn) void fn##_handler(Request req, Response *res)

URL_DECORATOR(img) {
    char path[1024];
    snprintf(path, sizeof(path), "images/%s", req.name);
    send_file(res, path);
}

int main() {
    // Simulate a request for /img?name=image.png
    Request req = {.name = "image.png"};
    Response res;
    img_handler(req, &res);
    
    if (res.file) {
        printf("File opened successfully.\n");
        fclose(res.file);
    } else {
        printf("Failed to open file.\n");
    }
    
    return 0;
}