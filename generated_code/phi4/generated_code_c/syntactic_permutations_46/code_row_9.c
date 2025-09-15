#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function prototypes
const char* get_image_url(const char *name);
FILE* open_image_file(const char *filename);

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <image_name>\n", argv[0]);
        return 1;
    }

    const char *image_name = argv[1];
    FILE *file = open_image_file(image_name);

    if (!file) {
        fprintf(stderr, "Error opening file\n");
        return 2;
    }

    // Send image content to standard output
    char buffer[1024];
    size_t bytes_read;

    while ((bytes_read = fread(buffer, 1, sizeof(buffer), file)) > 0) {
        fwrite(buffer, 1, bytes_read, stdout);
    }

    fclose(file);
    return 0;
}

const char* get_image_url(const char *name) {
    static char url[256];
    snprintf(url, sizeof(url), "/img/%s", name);
    return url;
}

FILE* open_image_file(const char *filename) {
    FILE *file = fopen(filename, "rb");
    if (!file) {
        printf("HTTP/1.1 404 Not Found\r\nContent-Type: text/plain\r\nConnection: close\r\n\r\nFile not found.\n");
    }
    return file;
}
