#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Usage: %s <input_image_file> <output_image_file>\n", argv[0]);
        return 1;
    }

    FILE *inputFile = fopen(argv[1], "rb");
    if (!inputFile) {
        perror("Error opening input file");
        return 1;
    }

    FILE *outputFile = fopen(argv[2], "wb");
    if (!outputFile) {
        fclose(inputFile);
        perror("Error creating output file");
        return 1;
    }

    const size_t bufferSize = 1024;
    unsigned char buffer[bufferSize];
    size_t bytesRead;

    while ((bytesRead = fread(buffer, 1, bufferSize, inputFile)) > 0) {
        fwrite(buffer, 1, bytesRead, outputFile);
    }

    fclose(inputFile);
    fclose(outputFile);

    return 0;
}