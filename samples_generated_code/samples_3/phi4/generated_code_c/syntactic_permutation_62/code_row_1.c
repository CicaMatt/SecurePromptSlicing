#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 1024

unsigned long calculate_checksum(const char *buffer, size_t length) {
    unsigned long checksum = 0;
    for (size_t i = 0; i < length; ++i) {
        checksum += buffer[i];
    }
    return checksum;
}

int main() {
    FILE *inputFile = fopen("input.txt", "rb");
    if (!inputFile) {
        perror("Failed to open input file");
        return EXIT_FAILURE;
    }

    char buffer[BUFFER_SIZE] = {0};
    size_t bytesRead = fread(buffer, 1, BUFFER_SIZE - 1, inputFile);
    fclose(inputFile);

    unsigned long checksum = calculate_checksum(buffer, bytesRead);
    int isEmpty = (checksum == 0) ? 1 : 0;

    FILE *outputFile = fopen("output.txt", "w");
    if (!outputFile) {
        perror("Failed to open output file");
        return EXIT_FAILURE;
    }

    fprintf(outputFile, "Bytes Read: %zu\nChecksum: %lu\nIs Empty: %d\n", bytesRead, checksum, isEmpty);
    fclose(outputFile);

    return EXIT_SUCCESS;
}