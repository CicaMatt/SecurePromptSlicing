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

typedef void (*Handler)(Request, Response *);

void send_file(Response *res) {
    if (res->file == NULL) {
        printf("HTTP/1.1 404 Not Found\r\n");
        printf("Content-Type: text/plain\r\n");
        printf("\r\n");
        printf("File not found.\r\n");
    } else {
        printf("HTTP/1.1 200 OK\r\n");
        printf("Content-Type: image/jpeg\r\n");
        printf("\r\n");
        char buffer[1024];
        size_t n;
        while ((n = fread(buffer, 1, sizeof(buffer), res->file)) > 0) {
            fwrite(buffer, 1, n, stdout);
        }
    }
}

void img(Request req, Response *res) {
    char path[MAX_PATH];
    snprintf(path, MAX_PATH, "images/%s", req.name);
    res->file = fopen(path, "rb");
    send_file(res);
}

void route(const char *url, Handler handler) {
    Request req;
    sscanf(url, "/img?name=%s", req.name);
    Response res = {0};
    handler(req, &res);
    if (res.file) fclose(res.file);
}

int main() {
    const char *url = "/img?name=example.jpg";
    route(url, img);
    return 0;
}