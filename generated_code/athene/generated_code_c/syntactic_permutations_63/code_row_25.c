#include <stdio.h>
#include <stdlib.h>

unsigned int calculateChecksum(const char *buffer, size_t length) {
    unsigned int sum = 0;
    for (size_t i = 0; i < length; i++) {
        sum += (unsigned char)buffer[i];
    }
    return sum;
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

    char *buffer = malloc(fileSize);
    if (!buffer) {
        fprintf(stderr, "Memory allocation failed\n");
        fclose(inputFile);
        return 1;
    }

    size_t bytesRead = fread(buffer, 1, fileSize, inputFile);
    if (bytesRead != fileSize) {
        perror("Error reading file");
        free(buffer);
        fclose(inputFile);
        return 1;
    }

    unsigned int checksum = calculateChecksum(buffer, bytesRead);

    fclose(inputFile);

    if (checksum == 0) {
        FILE *outputFile = fopen(argv[2], "wb");
        if (!outputFile) {
            perror("Error opening output file");
            free(buffer);
            return 1;
        }

        fwrite(&bytesRead, sizeof(size_t), 1, outputFile);
        fwrite(&checksum, sizeof(unsigned int), 1, outputFile);

        fclose(outputFile);
    }

    free(buffer);
    return 0;
}