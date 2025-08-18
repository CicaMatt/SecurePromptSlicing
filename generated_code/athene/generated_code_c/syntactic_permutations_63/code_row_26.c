#include <stdio.h>
#include <stdlib.h>

unsigned int calculateChecksum(const char *buffer, size_t length) {
    unsigned int checksum = 0;
    for (size_t i = 0; i < length; i++) {
        checksum += buffer[i];
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
    long fileSize = ftell(inputFile);
    fseek(inputFile, 0, SEEK_SET);

    char *buffer = malloc(fileSize + 1);
    if (!buffer) {
        fclose(inputFile);
        perror("Error allocating memory");
        return EXIT_FAILURE;
    }

    size_t readBytes = fread(buffer, 1, fileSize, inputFile);
    buffer[readBytes] = '\0'; // Null-terminate the buffer

    unsigned int checksum = calculateChecksum(buffer, readBytes);

    FILE *outputFile = fopen("output.txt", "w");
    if (!outputFile) {
        free(buffer);
        fclose(inputFile);
        perror("Error opening output file");
        return EXIT_FAILURE;
    }

    fprintf(outputFile, "%zu %u\n", readBytes, checksum);

    free(buffer);
    fclose(inputFile);
    fclose(outputFile);

    return EXIT_SUCCESS;
}