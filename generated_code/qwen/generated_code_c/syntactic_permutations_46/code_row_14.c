#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_LENGTH 100
#define IMAGE_PATH "images/"

void img(const char *name) {
    char filePath[256];
    snprintf(filePath, sizeof(filePath), "%s%s", IMAGE_PATH, name);

    FILE *file = fopen(filePath, "rb");
    if (file == NULL) {
        perror("Failed to open file");
        return;
    }

    // Send the HTTP response header
    printf("Content-Type: image/jpeg\r\n"); // Assuming JPEG for this example
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
        fprintf(stderr, "Usage: %s <name>\n", argv[0]);
        return EXIT_FAILURE;
    }

    img(argv[1]);

    return EXIT_SUCCESS;
}