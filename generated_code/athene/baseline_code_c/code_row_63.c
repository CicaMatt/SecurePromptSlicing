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
        return 1;
    }

    const char *inputFile = argv[1];
    const char *outputFile = argv[2];

    FILE *fp = fopen(inputFile, "rb");
    if (fp == NULL) {
        perror("Error opening file");
        return 1;
    }

    fseek(fp, 0, SEEK_END);
    long fileSize = ftell(fp);
    fseek(fp, 0, SEEK_SET);

    unsigned char *buffer = malloc(fileSize);
    if (buffer == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        fclose(fp);
        return 1;
    }

    size_t bytesRead = fread(buffer, 1, fileSize, fp);
    fclose(fp);

    unsigned int checksum = calculateChecksum(buffer, bytesRead);

    FILE *out = fopen(outputFile, "w");
    if (out == NULL) {
        perror("Error opening output file");
        free(buffer);
        return 1;
    }

    fprintf(out, "%zu %u\n", bytesRead, checksum);

    fclose(out);
    free(buffer);

    return 0;
}