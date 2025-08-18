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

    FILE *file = fopen(inputFile, "rb");
    if (!file) {
        perror("fopen");
        return 1;
    }

    fseek(file, 0, SEEK_END);
    long fileSize = ftell(file);
    fseek(file, 0, SEEK_SET);

    char *buffer = malloc(fileSize);
    if (!buffer) {
        fprintf(stderr, "Memory allocation failed\n");
        fclose(file);
        return 1;
    }

    size_t bytesRead = fread(buffer, 1, fileSize, file);
    unsigned int checksum = calculateChecksum(buffer, bytesRead);

    fclose(file);
    free(buffer);

    FILE *outFile = fopen(outputFile, "w");
    if (!outFile) {
        perror("fopen");
        return 1;
    }

    fprintf(outFile, "%zu\n%u\n", bytesRead, checksum);
    fclose(outFile);

    return 0;
}