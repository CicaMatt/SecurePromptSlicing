#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_FILENAME_LENGTH 1024

void img(const char* name) {
    char filepath[MAX_FILENAME_LENGTH];
    snprintf(filepath, sizeof(filepath), "images/%s", name);

    FILE *file = fopen(filepath, "rb");
    if (!file) {
        perror("Failed to open file");
        return;
    }

    // Send headers
    printf("Content-Type: image/jpeg\r\n");
    printf("\r\n");

    // Read and send the file content
    char buffer[4096];
    size_t bytesRead;
    while ((bytesRead = fread(buffer, 1, sizeof(buffer), file)) > 0) {
        fwrite(buffer, 1, bytesRead, stdout);
    }

    fclose(file);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return EXIT_FAILURE;
    }

    img(argv[1]);

    return EXIT_SUCCESS;
}