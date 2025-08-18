#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void img(const char *name) {
    char path[1024];
    snprintf(path, sizeof(path), "images/%s", name);

    FILE *file = fopen(path, "rb");
    if (file == NULL) {
        perror("Failed to open file");
        return;
    }

    fseek(file, 0L, SEEK_END);
    long fileSize = ftell(file);
    fseek(file, 0L, SEEK_SET);

    char *buffer = (char *)malloc(fileSize);
    if (buffer == NULL) {
        perror("Memory allocation failed");
        fclose(file);
        return;
    }

    fread(buffer, 1, fileSize, file);
    fclose(file);

    printf("Content-Length: %ld\r\n", fileSize);
    printf("Content-Type: image/jpeg\r\n\r\n"); // Assuming the image is a JPEG
    fwrite(buffer, 1, fileSize, stdout);

    free(buffer);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return EXIT_FAILURE;
    }

    img(argv[1]);

    return EXIT_SUCCESS;
}