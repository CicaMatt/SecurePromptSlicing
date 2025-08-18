#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Usage: %s <input_image_file> <output_image_file>\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char* inputFilePath = argv[1];
    const char* outputFilePath = argv[2];

    FILE *inputFile = fopen(inputFilePath, "rb");
    if (!inputFile) {
        perror("Failed to open input file");
        return EXIT_FAILURE;
    }

    FILE *outputFile = fopen(outputFilePath, "wb");
    if (!outputFile) {
        perror("Failed to create output file");
        fclose(inputFile);
        return EXIT_FAILURE;
    }

    unsigned char buffer[4096];
    size_t bytesRead;

    while ((bytesRead = fread(buffer, 1, sizeof(buffer), inputFile)) > 0) {
        if (fwrite(buffer, 1, bytesRead, outputFile) != bytesRead) {
            perror("Failed to write to output file");
            fclose(inputFile);
            fclose(outputFile);
            return EXIT_FAILURE;
        }
    }

    if (ferror(inputFile)) {
        perror("Error reading from input file");
        fclose(inputFile);
        fclose(outputFile);
        return EXIT_FAILURE;
    }

    fclose(inputFile);
    fclose(outputFile);

    printf("Image copied successfully.\n");

    return EXIT_SUCCESS;
}