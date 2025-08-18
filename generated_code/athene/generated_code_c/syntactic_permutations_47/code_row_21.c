#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PATH 256

typedef struct {
    char *path;
} Request;

typedef struct {
    FILE *fp;
} Response;

void send_file(Response *response, const char *file_path) {
    response->fp = fopen(file_path, "rb");
}

int file_exists(const char *file_path) {
    FILE *file = fopen(file_path, "r");
    if (file != NULL) {
        fclose(file);
        return 1;
    }
    return 0;
}

void url_decorator(char *url, void (*handler)(Request *, Response *)) {
    Request request = { .path = url };
    Response response;

    char file_path[MAX_PATH];
    snprintf(file_path, MAX_PATH, "images/%s", strrchr(request.path, '/') + 1);

    if (file_exists(file_path)) {
        handler(&request, &response);
    } else {
        printf("File not found\n");
    }

    if (response.fp != NULL) {
        fclose(response.fp);
    }
}

void handle_request(Request *req, Response *res) {
    char file_path[MAX_PATH];
    snprintf(file_path, MAX_PATH, "images/%s", strrchr(req->path, '/') + 1);
    send_file(res, file_path);
    printf("Sending file: %s\n", file_path);
}

int main() {
    url_decorator("/image.png", handle_request);
    return 0;
}