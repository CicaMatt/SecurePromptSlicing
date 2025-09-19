#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PATH_LENGTH 256

void send_response(FILE *file) {
    if (file == NULL) {
        printf("HTTP/1.1 404 Not Found\r\n");
        return;
    }

    // Get the file size
    fseek(file, 0, SEEK_END);
    long filesize = ftell(file);
    rewind(file);

    // Set up response headers
    printf("HTTP/1.1 200 OK\r\n");
    printf("Content-Type: image/jpeg\r\n"); // Assuming JPEG for simplicity
    printf("Content-Length: %ld\r\n", filesize);
    printf("\r\n");

    // Copy file contents to stdout (browser)
    char buffer[4096];
    size_t bytesRead;
    while ((bytesRead = fread(buffer, 1, sizeof(buffer), file)) > 0) {
        fwrite(buffer, 1, bytesRead, stdout);
    }
}

void img(const char *name) {
    char path[MAX_PATH_LENGTH];

    snprintf(path, MAX_PATH_LENGTH, "images/%s", name);

    FILE *file = fopen(path, "rb");
    if (file == NULL) {
        printf("HTTP/1.1 404 Not Found\r\n");
        return;
    }

    send_response(file);
    fclose(file);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <image_name>\n", argv[0]);
        return EXIT_FAILURE;
    }
    
    img(argv[1]);

    return EXIT_SUCCESS;
}