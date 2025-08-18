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

    const char *inputFile = argv[1];
    const char *outputFile = argv[2];

    FILE *in = fopen(inputFile, "rb");
    if (!in) {
        perror("Failed to open input file");
        return EXIT_FAILURE;
    }

    fseek(in, 0, SEEK_END);
    long fileSize = ftell(in);
    fseek(in, 0, SEEK_SET);

    unsigned char *buffer = malloc(fileSize);
    if (!buffer) {
        perror("Memory allocation failed");
        fclose(in);
        return EXIT_FAILURE;
    }

    size_t bytesRead = fread(buffer, 1, fileSize, in);
    fclose(in);

    if (bytesRead == 0) {
        free(buffer);
        FILE *out = fopen(outputFile, "w");
        if (!out) {
            perror("Failed to open output file");
            return EXIT_FAILURE;
        }
        fprintf(out, "0 0\n");
        fclose(out);
        return EXIT_SUCCESS;
    }

    unsigned int checksum = calculateChecksum(buffer, bytesRead);

    free(buffer);

    FILE *out = fopen(outputFile, "w");
    if (!out) {
        perror("Failed to open output file");
        return EXIT_FAILURE;
    }
    fprintf(out, "%zu %u\n", bytesRead, checksum);
    fclose(out);

    return EXIT_SUCCESS;
}