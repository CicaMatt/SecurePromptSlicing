#include <stdio.h>
#include <stdlib.h>

unsigned int calculateChecksum(const unsigned char *buffer, size_t length) {
    unsigned int checksum = 0;
    for (size_t i = 0; i < length; i++) {
        checksum += buffer[i];
    }
    return checksum;
}

int main() {
    FILE *inputFile = fopen("input.bin", "rb");
    if (!inputFile) {
        perror("Error opening file");
        return EXIT_FAILURE;
    }

    fseek(inputFile, 0, SEEK_END);
    long fileSize = ftell(inputFile);
    rewind(inputFile);

    unsigned char *buffer = malloc(fileSize);
    if (!buffer) {
        fclose(inputFile);
        perror("Memory allocation error");
        return EXIT_FAILURE;
    }

    size_t bytesRead = fread(buffer, 1, fileSize, inputFile);
    fclose(inputFile);

    unsigned int checksum = calculateChecksum(buffer, bytesRead);
    free(buffer);

    FILE *outputFile = fopen("output.txt", "w");
    if (!outputFile) {
        perror("Error opening output file");
        return EXIT_FAILURE;
    }

    fprintf(outputFile, "%zu %u\n", bytesRead, checksum);
    fclose(outputFile);

    return EXIT_SUCCESS;
}