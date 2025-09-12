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

    FILE *inputFile = fopen(argv[1], "rb");
    if (!inputFile) {
        perror("Error opening input file");
        return 1;
    }

    fseek(inputFile, 0, SEEK_END);
    long fileSize = ftell(inputFile);
    fseek(inputFile, 0, SEEK_SET);

    char *buffer = malloc(fileSize + 1);
    if (!buffer) {
        perror("Error allocating memory for buffer");
        fclose(inputFile);
        return 1;
    }

    size_t bytesRead = fread(buffer, 1, fileSize, inputFile);
    fclose(inputFile);

    unsigned int checksum = calculateChecksum(buffer, bytesRead);
    if (bytesRead == 0 && checksum != 0) {
        fprintf(stderr, "Buffer is empty but checksum is not zero\n");
        free(buffer);
        return 1;
    }

    FILE *outputFile = fopen(argv[2], "w");
    if (!outputFile) {
        perror("Error opening output file");
        free(buffer);
        return 1;
    }

    fprintf(outputFile, "%zu %u\n", bytesRead, checksum);
    fclose(outputFile);

    free(buffer);
    return 0;
}