#include <stdio.h>
#include <stdlib.h>

unsigned char calculate_checksum(unsigned char *buffer, size_t length) {
    unsigned char sum = 0;
    for (size_t i = 0; i < length; i++) {
        sum += buffer[i];
    }
    return sum;
}

int main() {
    FILE *inputFile = fopen("input.bin", "rb");
    if (!inputFile) {
        perror("Failed to open input file");
        exit(EXIT_FAILURE);
    }

    const size_t bufferSize = 1024;
    unsigned char buffer[bufferSize];
    size_t bytesRead = fread(buffer, 1, bufferSize, inputFile);

    fclose(inputFile);

    unsigned char checksum = calculate_checksum(buffer, bytesRead);

    FILE *outputFile = fopen("output.txt", "w");
    if (!outputFile) {
        perror("Failed to open output file");
        exit(EXIT_FAILURE);
    }

    fprintf(outputFile, "Bytes read: %zu\nChecksum: %u\n", bytesRead, checksum);
    fclose(outputFile);

    return 0;
}