#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 1024

void send_response(FILE *file) {
    char buffer[BUFFER_SIZE];
    size_t bytes_read;
    
    // Set headers for image content type
    printf("Content-Type: image/jpeg\n");
    printf("\n");

    while ((bytes_read = fread(buffer, 1, BUFFER_SIZE, file)) > 0) {
        fwrite(buffer, 1, bytes_read, stdout);
    }
}

void img(const char *name) {
    char filepath[256];
    snprintf(filepath, sizeof(filepath), "images/%s", name);

    FILE *file = fopen(filepath, "rb");
    if (file == NULL) {
        printf("Content-Type: text/html\n\n");
        printf("<html><body><h1>404 Not Found</h1></body></html>");
    } else {
        send_response(file);
        fclose(file);
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <image_name>\n", argv[0]);
        return EXIT_FAILURE;
    }

    img(argv[1]);

    return EXIT_SUCCESS;
}