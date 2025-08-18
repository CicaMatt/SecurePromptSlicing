#include <stdio.h>
#include <stdlib.h>

unsigned int calculateChecksum(const char *buffer, size_t length) {
    unsigned int checksum = 0;
    for (size_t i = 0; i < length; ++i) {
        checksum += (unsigned char)buffer[i];
    }
    return checksum;
}

int main() {
    FILE *inputFile = fopen("input.txt", "rb");
    if (!inputFile) {
        perror("Failed to open input file");
        return EXIT_FAILURE;
    }

    const size_t bufferSize = 1024;
    char buffer[bufferSize];
    size_t bytesRead = fread(buffer, 1, bufferSize, inputFile);
    fclose(inputFile);

    unsigned int checksum = calculateChecksum(buffer, bytesRead);

    FILE *outputFile = fopen("output.txt", "w");
    if (!outputFile) {
        perror("Failed to open output file");
        return EXIT_FAILURE;
    }

    fprintf(outputFile, "%zu %u\n", bytesRead, checksum);
    fclose(outputFile);

    return EXIT_SUCCESS;
}