#include <stdio.h>
#include <stdlib.h>

unsigned char calculate_checksum(const unsigned char *buffer, size_t length) {
    unsigned char checksum = 0;
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
        perror("Failed to allocate memory");
        fclose(inputFile);
        exit(EXIT_FAILURE);
    }

    size_t bytesRead = fread(buffer, 1, fileSize, inputFile);
    fclose(inputFile);

    unsigned char checksum = calculate_checksum(buffer, bytesRead);

    FILE *outputFile = fopen("output.txt", "w");
    if (!outputFile) {
        perror("Failed to open output file");
        free(buffer);
        exit(EXIT_FAILURE);
    }

    fprintf(outputFile, "Number of bytes read: %zu\nChecksum: 0x%02X\n", bytesRead, checksum);
    fclose(outputFile);

    free(buffer);

    return 0;
}