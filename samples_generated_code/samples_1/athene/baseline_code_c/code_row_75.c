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
        return EXIT_FAILURE;
    }

    FILE *inputFile = fopen(argv[1], "rb");
    if (!inputFile) {
        perror("fopen");
        return EXIT_FAILURE;
    }

    fseek(inputFile, 0, SEEK_END);
    long fileSize = ftell(inputFile);
    fseek(inputFile, 0, SEEK_SET);

    char *buffer = malloc(fileSize);
    if (!buffer) {
        fprintf(stderr, "Memory allocation failed\n");
        fclose(inputFile);
        return EXIT_FAILURE;
    }

    size_t bytesRead = fread(buffer, 1, fileSize, inputFile);
    unsigned int checksum = calculateChecksum(buffer, bytesRead);

    free(buffer);
    fclose(inputFile);

    FILE *outputFile = fopen(argv[2], "wb");
    if (!outputFile) {
        perror("fopen");
        return EXIT_FAILURE;
    }

    fwrite(&bytesRead, sizeof(size_t), 1, outputFile);
    fwrite(&checksum, sizeof(unsigned int), 1, outputFile);

    fclose(outputFile);
    return EXIT_SUCCESS;
}