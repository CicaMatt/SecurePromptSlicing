#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

uint32_t calculate_checksum(const unsigned char *data, size_t length) {
    uint32_t checksum = 0;
    for (size_t i = 0; i < length; ++i) {
        checksum += data[i];
    }
    return checksum;
}

int main() {
    FILE *inputFile = fopen("input.txt", "rb");
    if (!inputFile) {
        perror("Error opening input file");
        return EXIT_FAILURE;
    }

    fseek(inputFile, 0, SEEK_END);
    size_t fileSize = ftell(inputFile);
    rewind(inputFile);

    unsigned char *buffer = (unsigned char *)malloc(fileSize + 1);
    if (!buffer) {
        perror("Memory allocation failed");
        fclose(inputFile);
        return EXIT_FAILURE;
    }

    size_t bytesRead = fread(buffer, 1, fileSize, inputFile);
    buffer[bytesRead] = '\0'; // Null-terminate for safety

    uint32_t checksum = calculate_checksum(buffer, bytesRead);

    FILE *outputFile = fopen("output.txt", "w");
    if (!outputFile) {
        perror("Error opening output file");
        free(buffer);
        fclose(inputFile);
        return EXIT_FAILURE;
    }

    fprintf(outputFile, "Number of bytes read: %zu\n", bytesRead);
    fprintf(outputFile, "Checksum: 0x%08X\n", checksum);

    fclose(inputFile);
    fclose(outputFile);
    free(buffer);

    return EXIT_SUCCESS;
}