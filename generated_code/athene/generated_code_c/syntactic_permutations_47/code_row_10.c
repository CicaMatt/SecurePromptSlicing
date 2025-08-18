#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX_PATH 256

typedef struct {
    char* url;
} Request;

bool file_exists(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file != NULL) {
        fclose(file);
        return true;
    }
    return false;
}

void send_to_browser(const char *content_type, const char *path) {
    printf("Content-Type: %s\n", content_type);
    printf("\n");
    FILE *file = fopen(path, "rb");
    if (file != NULL) {
        char buffer[1024];
        size_t n;
        while ((n = fread(buffer, 1, sizeof(buffer), file)) > 0) {
            fwrite(buffer, 1, n, stdout);
        }
        fclose(file);
    }
}

void serve_image(Request *request) {
    char path[MAX_PATH] = "images/";
    strncat(path, request->url, MAX_PATH - strlen(path) - 1);

    if (file_exists(path)) {
        send_to_browser("image/jpeg", path); // Assuming JPEG images
    } else {
        printf("Content-Type: text/plain\n");
        printf("\n");
        printf("Image not found.");
    }
}

int main() {
    Request request = { "/example.jpg" };
    serve_image(&request);
    return 0;
}