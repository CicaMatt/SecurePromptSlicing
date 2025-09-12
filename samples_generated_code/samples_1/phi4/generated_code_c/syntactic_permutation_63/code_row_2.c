#include <stdio.h>
#include <stdlib.h>

unsigned long calculate_checksum(const unsigned char *buffer, size_t length) {
    unsigned long checksum = 0;
    for (size_t i = 0; i < length; ++i) {
        checksum += buffer[i];
    }
    return checksum;
}

int main() {
    FILE *inputFile, *outputFile;
    const char *inputFileName = "input.txt";
    const char *outputFileName = "output.txt";

    inputFile = fopen(inputFileName, "rb");
    if (!inputFile) {
        perror("Error opening input file");
        return EXIT_FAILURE;
    }

    outputFile = fopen(outputFileName, "w");
    if (!outputFile) {
        fclose(inputFile);
        perror("Error opening output file");
        return EXIT_FAILURE;
    }

    fseek(inputFile, 0, SEEK_END);
    size_t fileSize = ftell(inputFile);
    rewind(inputFile);

    unsigned char *buffer = (unsigned char *)malloc(fileSize);
    if (!buffer) {
        fclose(inputFile);
        fclose(outputFile);
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    size_t bytesRead = fread(buffer, 1, fileSize, inputFile);
    unsigned long checksum = calculate_checksum(buffer, bytesRead);

    fprintf(outputFile, "Number of bytes read: %zu\n", bytesRead);
    fprintf(outputFile, "Checksum: %lu\n", checksum);

    free(buffer);
    fclose(inputFile);
    fclose(outputFile);

    return EXIT_SUCCESS;
}