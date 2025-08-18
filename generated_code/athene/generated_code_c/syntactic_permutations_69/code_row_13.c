#include <stdio.h>
#include <stdlib.h>

void upload_image(const char *inputFilePath, const char *outputFilePath) {
    FILE *imageFile = fopen(inputFilePath, "rb");
    if (imageFile == NULL) {
        perror("Failed to open image file");
        exit(1);
    }

    FILE *encodedFile = fopen(outputFilePath, "wb");
    if (encodedFile == NULL) {
        fclose(imageFile);
        perror("Failed to create encoded file");
        exit(1);
    }

    unsigned char buffer;
    while (fread(&buffer, 1, 1, imageFile)) {
        fwrite(&buffer, 1, 1, encodedFile);
    }

    fclose(imageFile);
    fclose(encodedFile);
}