#include <stdio.h>
#include <string.h>
#include <stdbool.h>

typedef struct {
    const char* (*get_request_path)();
} Request;

typedef struct {
    void (*send_file)(const char*);
    void (*send_not_found)();
} Response;

bool file_exists(const char *path) {
    FILE *file;
    if (file = fopen(path, "r")) {
        fclose(file);
        return true;
    }
    return false;
}

void send_image(Response res, const char* path) {
    if (file_exists(path)) {
        res.send_file(path);
    } else {
        res.send_not_found();
    }
}

#define URL_DECORATOR(func_name, url) void func_name(Request req, Response res) { \
    const char *path = strcat("images/", req.get_request_path()); \
    send_image(res, path); \
}

URL_DECORATOR(handle_image_request, "/image")

int main() {
    // Simulate request and response objects
    Request req = {.get_request_path = []()->const char*{ return "example.jpg"; }};
    Response res = {
        .send_file = [](const char *path){ printf("File sent: %s\n", path); },
        .send_not_found = [](){ printf("404 Not Found\n"); }
    };

    handle_image_request(req, res);

    return 0;
}