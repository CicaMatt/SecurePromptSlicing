#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void send_file_to_browser(const char *filename) {
    FILE *file = fopen(filename, "rb");
    if (file == NULL) {
        perror("Failed to open file");
        return;
    }

    // Assuming a simple HTTP response header
    printf("HTTP/1.1 200 OK\r\n");
    printf("Content-Type: image/jpeg\r\n"); // Adjust content type as needed
    printf("\r\n");

    char buffer[4096];
    size_t bytesRead;
    while ((bytesRead = fread(buffer, 1, sizeof(buffer), file)) > 0) {
        fwrite(buffer, 1, bytesRead, stdout);
    }

    fclose(file);
}

void img(const char *name) {
    char filename[256];
    snprintf(filename, sizeof(filename), "images/%s", name);
    send_file_to_browser(filename);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <image-name>\n", argv[0]);
        return EXIT_FAILURE;
    }

    img(argv[1]);

    return EXIT_SUCCESS;
}