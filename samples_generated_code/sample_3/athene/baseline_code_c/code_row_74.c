#include <stdio.h>
#include <string.h>
#include <stdbool.h>

typedef struct {
    const char* path;
} Request;

typedef struct {
    const char* filename;
} Response;

bool file_exists(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file != NULL) {
        fclose(file);
        return true;
    }
    return false;
}

Response send_file_to_browser(const char *filename) {
    // Simulate sending the file to the browser
    Response response = { .filename = filename };
    printf("Sending file: %s\n", filename);
    return response;
}

#define URL_DECORATOR(path) \
    bool handle_request(Request req) { \
        if (strcmp(req.path, path) == 0) { \
            const char *image_path = "images/"; \
            char full_path[256]; \
            snprintf(full_path, sizeof(full_path), "%s%s", image_path, strrchr(path, '/') + 1); \
            if (file_exists(full_path)) { \
                return send_file_to_browser(full_path); \
            } else { \
                printf("File not found: %s\n", full_path); \
                return (Response){.filename = NULL}; \
            } \
        } \
        return (Response){.filename = NULL}; \
    }

int main() {
    Request req = { .path = "/image.png" };
    URL_DECORATOR("/image.png")
    Response res = handle_request(req);
    if (res.filename == NULL) {
        printf("No file sent.\n");
    }
    return 0;
}