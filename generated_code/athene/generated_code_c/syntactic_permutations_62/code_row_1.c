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
    if (argc != 3) {
        fprintf(stderr, "Usage: %s input_file output_file\n", argv[0]);
        return 1;
    }

    const char *inputFile = argv[1];
    const char *outputFile = argv[2];

    FILE *fpIn = fopen(inputFile, "rb");
    if (!fpIn) {
        perror("Error opening input file");
        return 1;
    }

    fseek(fpIn, 0, SEEK_END);
    long fileSize = ftell(fpIn);
    fseek(fpIn, 0, SEEK_SET);

    char *buffer = malloc(fileSize);
    if (!buffer) {
        fprintf(stderr, "Memory allocation failed\n");
        fclose(fpIn);
        return 1;
    }

    size_t bytesRead = fread(buffer, 1, fileSize, fpIn);
    unsigned int checksum = calculateChecksum(buffer, bytesRead);

    fclose(fpIn);
    free(buffer);

    FILE *fpOut = fopen(outputFile, "w");
    if (!fpOut) {
        perror("Error opening output file");
        return 1;
    }

    fprintf(fpOut, "%zu %u\n", bytesRead, checksum);
    fclose(fpOut);

    return 0;
}