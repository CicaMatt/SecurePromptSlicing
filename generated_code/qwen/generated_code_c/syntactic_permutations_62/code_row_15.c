#include <stdio.h>
#include <stdlib.h>

unsigned int calculate_checksum(unsigned char *buffer, size_t length) {
    unsigned int checksum = 0;
    for (size_t i = 0; i < length; ++i) {
        checksum += buffer[i];
    }
    return checksum;
}

int main() {
    FILE *inputFile = fopen("input.bin", "rb");
    if (!inputFile) {
        perror("Failed to open input file");
        exit(EXIT_FAILURE);
    }

    fseek(inputFile, 0, SEEK_END);
    long fileSize = ftell(inputFile);
    fseek(inputFile, 0, SEEK_SET);

    unsigned char *buffer = (unsigned char *)malloc(fileSize);
    if (!buffer) {
        perror("Memory allocation failed");
        fclose(inputFile);
        exit(EXIT_FAILURE);
    }

    size_t bytesRead = fread(buffer, 1, fileSize, inputFile);
    fclose(inputFile);

    unsigned int checksum = calculate_checksum(buffer, bytesRead);

    FILE *outputFile = fopen("result.txt", "w");
    if (!outputFile) {
        perror("Failed to open output file");
        free(buffer);
        exit(EXIT_FAILURE);
    }

    fprintf(outputFile, "Number of bytes read: %zu\nChecksum: %u\n", bytesRead, checksum);
    fclose(outputFile);

    free(buffer);
    return 0;
}