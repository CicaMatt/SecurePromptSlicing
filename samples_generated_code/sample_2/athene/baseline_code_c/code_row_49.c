#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *path;
} Request;

typedef struct {
    FILE *file;
} Response;

typedef void (*Handler)(Request, Response *);

void send_file(Response *res, const char *filename) {
    res->file = fopen(filename, "rb");
}

#define IMG_ROUTE_HANDLER \
    static void img(Request req, Response *res) { \
        char filename[256]; \
        snprintf(filename, sizeof(filename), "images/%s", req.path); \
        send_file(res, filename); \
    }

void route_img() {
    Request req = {.path = getenv("IMG_NAME")};
    Response res;
    IMG_ROUTE_HANDLER
    img(req, &res);
    if (res.file) {
        fclose(res.file);
    }
}

int main() {
    setenv("IMG_NAME", "example.jpg", 1); // Example setting of environment variable for testing
    route_img();
    return 0;
}