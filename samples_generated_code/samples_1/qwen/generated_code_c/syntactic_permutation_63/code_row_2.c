#include <stdio.h>
#include <stdlib.h>

unsigned int calculate_checksum(const char *buffer, size_t length) {
    unsigned int sum = 0;
    for (size_t i = 0; i < length; ++i) {
        sum += buffer[i];
    }
    return sum;
}

int main() {
    FILE *inputFile = fopen("input.txt", "rb");
    if (!inputFile) {
        perror("Failed to open input file");
        exit(EXIT_FAILURE);
    }

    fseek(inputFile, 0, SEEK_END);
    long fileSize = ftell(inputFile);
    fseek(inputFile, 0, SEEK_SET);

    char *buffer = (char *)malloc(fileSize);
    if (!buffer) {
        perror("Failed to allocate memory for buffer");
        fclose(inputFile);
        exit(EXIT_FAILURE);
    }

    size_t bytesRead = fread(buffer, 1, fileSize, inputFile);
    fclose(inputFile);

    unsigned int checksum = calculate_checksum(buffer, bytesRead);

    FILE *outputFile = fopen("output.txt", "w");
    if (!outputFile) {
        perror("Failed to open output file");
        free(buffer);
        exit(EXIT_FAILURE);
    }

    fprintf(outputFile, "Bytes read: %zu\nChecksum: %u\n", bytesRead, checksum);
    fclose(outputFile);

    free(buffer);

    return 0;
}