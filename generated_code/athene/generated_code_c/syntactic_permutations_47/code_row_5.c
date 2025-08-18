#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define IMAGES_FOLDER "images/"
#define BUFFER_SIZE 1024

typedef int (*Handler)(const char*);

int send_file_to_browser(const char *file_path) {
    FILE *fp = fopen(file_path, "rb");
    if (fp == NULL) return 0;

    // Send HTTP headers
    printf("Content-Type: image/jpeg\n");
    printf("\n");

    // Send file content
    char buffer[BUFFER_SIZE];
    size_t n;
    while ((n = fread(buffer, 1, BUFFER_SIZE, fp)) > 0) {
        fwrite(buffer, 1, n, stdout);
    }

    fclose(fp);
    return 1;
}

int check_file_exists(const char *file_name, Handler handler) {
    char file_path[256];
    snprintf(file_path, sizeof(file_path), "%s%s", IMAGES_FOLDER, file_name);

    if (access(file_path, F_OK) == -1) {
        printf("HTTP/1.1 404 Not Found\n");
        printf("Content-Type: text/plain\n");
        printf("\n");
        printf("File not found.\n");
        return 0;
    }

    return handler(file_path);
}

int handle_image_request(const char *file_name) {
    return check_file_exists(file_name, send_file_to_browser);
}

int main(int argc, char **argv) {
    if (argc != 2) {
        printf("HTTP/1.1 400 Bad Request\n");
        printf("Content-Type: text/plain\n");
        printf("\n");
        printf("Usage: %s <image_filename>\n", argv[0]);
        return 1;
    }

    handle_image_request(argv[1]);

    return 0;
}