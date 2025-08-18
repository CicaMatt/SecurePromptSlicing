#include <stdio.h>
#include <stdlib.h>

unsigned int calculateChecksum(const char *buffer, size_t length) {
    unsigned int checksum = 0;
    for (size_t i = 0; i < length; i++) {
        checksum += (unsigned char)buffer[i];
    }
    return checksum;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    const char *inputFilename = argv[1];
    FILE *inputFile = fopen(inputFilename, "rb");
    if (!inputFile) {
        perror("Error opening file");
        return 1;
    }

    fseek(inputFile, 0, SEEK_END);
    long fileSize = ftell(inputFile);
    fseek(inputFile, 0, SEEK_SET);

    char *buffer = malloc(fileSize);
    if (!buffer) {
        perror("Memory allocation error");
        fclose(inputFile);
        return 1;
    }

    size_t bytesRead = fread(buffer, 1, fileSize, inputFile);
    fclose(inputFile);

    unsigned int checksum = calculateChecksum(buffer, bytesRead);
    free(buffer);

    const char *outputFilename = "result.txt";
    FILE *outputFile = fopen(outputFilename, "w");
    if (!outputFile) {
        perror("Error opening output file");
        return 1;
    }

    fprintf(outputFile, "%zu %u\n", bytesRead, checksum);
    fclose(outputFile);

    return 0;
}