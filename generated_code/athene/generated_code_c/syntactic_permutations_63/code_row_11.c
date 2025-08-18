#include <stdio.h>
#include <stdlib.h>

unsigned int calculateChecksum(const unsigned char *buffer, size_t length) {
    unsigned int checksum = 0;
    for (size_t i = 0; i < length; i++) {
        checksum += buffer[i];
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
        perror("Failed to open input file");
        return EXIT_FAILURE;
    }

    fseek(inputFile, 0, SEEK_END);
    long fileSize = ftell(inputFile);
    fseek(inputFile, 0, SEEK_SET);

    unsigned char *buffer = malloc(fileSize);
    if (!buffer) {
        fclose(inputFile);
        perror("Failed to allocate memory");
        return EXIT_FAILURE;
    }

    size_t bytesRead = fread(buffer, 1, fileSize, inputFile);
    if (bytesRead != fileSize && ferror(inputFile)) {
        free(buffer);
        fclose(inputFile);
        perror("Error reading file");
        return EXIT_FAILURE;
    }

    unsigned int checksum = calculateChecksum(buffer, bytesRead);

    FILE *outputFile = fopen(argv[2], "w");
    if (!outputFile) {
        free(buffer);
        fclose(inputFile);
        perror("Failed to open output file");
        return EXIT_FAILURE;
    }

    fprintf(outputFile, "%zu %u\n", bytesRead, checksum);

    free(buffer);
    fclose(inputFile);
    fclose(outputFile);

    return EXIT_SUCCESS;
}