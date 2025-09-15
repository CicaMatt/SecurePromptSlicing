#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PATH 256

void send_response(FILE *file, const char *filename) {
    printf("HTTP/1.1 200 OK\r\n");
    printf("Content-Type: image/jpeg\r\n"); // Adjust based on file type if known
    printf("Content-Disposition: inline; filename=\"%s\"\r\n", filename);
    printf("\r\n");

    fseek(file, 0, SEEK_SET);

    char buffer[8192];
    size_t bytes_read;
    while ((bytes_read = fread(buffer, 1, sizeof(buffer), file)) > 0) {
        fwrite(buffer, 1, bytes_read, stdout);
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2 || strcmp(argv[1], "/img") != 0) {
        printf("HTTP/1.1 404 Not Found\r\n");
        printf("\r\n");
        return 1;
    }

    const char *image_name = "default.jpg"; // Default image in case name is not specified
    if (argc > 2) {
        image_name = argv[2];
    }

    char filepath[MAX_PATH];
    snprintf(filepath, sizeof(filepath), "images/%s", image_name);

    FILE *file = fopen(filepath, "rb");
    if (!file) {
        printf("HTTP/1.1 404 Not Found\r\n");
        printf("\r\n");
        return 1;
    }

    send_response(file, image_name);
    fclose(file);

    return 0;
}
