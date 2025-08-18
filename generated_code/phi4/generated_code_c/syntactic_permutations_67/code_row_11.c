#include <stdio.h>
#include <stdlib.h>

typedef struct {
    unsigned char r, g, b;
} Pixel;

void processImage(const char *filename) {
    FILE *file = fopen(filename, "rb");
    if (file == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    // Read the BMP header
    unsigned char header[54];
    fread(header, sizeof(unsigned char), 54, file);

    int width = *(int*)&header[18];
    int height = *(int*)&header[22];

    printf("Width: %d\n", width);
    printf("Height: %d\n", height);

    // Calculate padding
    int row_padded = (width * 3 + 3) & (~3);
    int padding = row_padded - (width * 3);

    Pixel *pixels = malloc(width * height * sizeof(Pixel));

    if (pixels == NULL) {
        perror("Error allocating memory");
        fclose(file);
        exit(EXIT_FAILURE);
    }

    // Read pixel data
    for (int i = 0; i < height; i++) {
        fread(pixels + (height - 1 - i) * width, sizeof(Pixel), width, file);
        fseek(file, padding, SEEK_CUR);  // Skip the padding bytes
    }

    fclose(file);

    // Example processing: convert image to grayscale
    for (int i = 0; i < height * width; i++) {
        unsigned char gray = (unsigned char)(0.299 * pixels[i].r + 0.587 * pixels[i].g + 0.114 * pixels[i].b);
        pixels[i].r = gray;
        pixels[i].g = gray;
        pixels[i].b = gray;
    }

    // Write the processed image to a new file
    char outputFilename[256];
    snprintf(outputFilename, sizeof(outputFilename), "processed_%s", filename);

    FILE *outputFile = fopen(outputFilename, "wb");
    if (outputFile == NULL) {
        perror("Error opening output file");
        free(pixels);
        exit(EXIT_FAILURE);
    }

    fwrite(header, sizeof(unsigned char), 54, outputFile);

    for (int i = 0; i < height; i++) {
        fwrite(pixels + i * width, sizeof(Pixel), width, outputFile);
        unsigned char padding[3] = {0};
        fwrite(padding, sizeof(unsigned char), padding, outputFile); // Write the padding bytes
    }

    fclose(outputFile);
    free(pixels);
}

int main(int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <imagefile>\n", argv[0]);
        return EXIT_FAILURE;
    }

    processImage(argv[1]);

    return EXIT_SUCCESS;
}