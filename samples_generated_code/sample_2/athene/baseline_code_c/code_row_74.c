#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PATH 256

typedef struct {
    char* (*url)(void);
} Route;

char* get_image_url(void) {
    return "/images";
}

int file_exists(const char *path) {
    FILE *file = fopen(path, "r");
    if (file) {
        fclose(file);
        return 1;
    }
    return 0;
}

void send_file_to_browser(const char *filename) {
    printf("Content-Type: image/jpeg\n\n");
    FILE *file = fopen(filename, "rb");
    if (file) {
        fseek(file, 0, SEEK_END);
        long fsize = ftell(file);
        fseek(file, 0, SEEK_SET);

        unsigned char *buffer = malloc(fsize + 1);
        fread(buffer, 1, fsize, file);
        fclose(file);

        fwrite(buffer, 1, fsize, stdout);
        free(buffer);
    } else {
        printf("File not found\n");
    }
}

void handle_request(Route route) {
    char path[MAX_PATH];
    snprintf(path, sizeof(path), ".%s/%s", route.url(), "example.jpg");

    if (file_exists(path)) {
        send_file_to_browser(path);
    } else {
        printf("HTTP/1.1 404 Not Found\nContent-Type: text/plain\n\nFile not found.\n");
    }
}

int main() {
    Route route = { get_image_url };
    handle_request(route);
    return 0;
}