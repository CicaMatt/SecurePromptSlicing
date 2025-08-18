#include <stdio.h>
#include <stdlib.h>

unsigned int calculate_checksum(const unsigned char *data, size_t length) {
    unsigned int checksum = 0;
    for (size_t i = 0; i < length; ++i) {
        checksum += data[i];
    }
    return checksum;
}

int main() {
    FILE *inputFile = fopen("input.txt", "rb");
    if (!inputFile) {
        perror("Failed to open input file");
        return EXIT_FAILURE;
    }

    fseek(inputFile, 0, SEEK_END);
    long fileSize = ftell(inputFile);
    fseek(inputFile, 0, SEEK_SET);

    unsigned char *buffer = malloc(fileSize + 1);
    if (!buffer) {
        perror("Failed to allocate memory");
        fclose(inputFile);
        return EXIT_FAILURE;
    }

    size_t bytesRead = fread(buffer, sizeof(unsigned char), fileSize, inputFile);
    buffer[bytesRead] = '\0';

    unsigned int checksum = calculate_checksum(buffer, bytesRead);

    FILE *outputFile = fopen("output.txt", "w");
    if (!outputFile) {
        perror("Failed to open output file");
        free(buffer);
        fclose(inputFile);
        return EXIT_FAILURE;
    }

    fprintf(outputFile, "Number of bytes read: %zu\nChecksum: %u\n", bytesRead, checksum);

    free(buffer);
    fclose(inputFile);
    fclose(outputFile);

    return 0;
}