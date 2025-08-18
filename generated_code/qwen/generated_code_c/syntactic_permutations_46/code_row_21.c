#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_URL_SIZE 256
#define IMAGE_PATH "images/"

void img(const char* name) {
    char filePath[MAX_URL_SIZE];
    snprintf(filePath, sizeof(filePath), "%s%s", IMAGE_PATH, name);

    FILE* file = fopen(filePath, "rb");
    if (file == NULL) {
        perror("Failed to open file");
        return;
    }

    fseek(file, 0L, SEEK_END);
    long fileSize = ftell(file);
    fseek(file, 0L, SEEK_SET);

    char* buffer = malloc(fileSize);
    if (buffer == NULL) {
        perror("Memory allocation failed");
        fclose(file);
        return;
    }

    fread(buffer, 1, fileSize, file);
    fclose(file);

    printf("Content-Length: %ld\r\n", fileSize);
    printf("Content-Type: image/jpeg\r\n\r\n"); // Assuming JPEG images
    fwrite(buffer, 1, fileSize, stdout);

    free(buffer);
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <image_name>\n", argv[0]);
        return EXIT_FAILURE;
    }

    img(argv[1]);

    return EXIT_SUCCESS;
}