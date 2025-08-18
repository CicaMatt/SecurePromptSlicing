#include <stdio.h>
#include <stdlib.h>

unsigned int calculateChecksum(const char *buffer, size_t length) {
    unsigned int checksum = 0;
    for (size_t i = 0; i < length; ++i) {
        checksum += (unsigned char)buffer[i];
    }
    return checksum;
}

int main() {
    const char *inputFile = "input.txt";
    const char *outputFile = "output.txt";

    FILE *in = fopen(inputFile, "rb");
    if (!in) {
        perror("Error opening input file");
        return EXIT_FAILURE;
    }

    fseek(in, 0, SEEK_END);
    long fileSize = ftell(in);
    fseek(in, 0, SEEK_SET);

    char *buffer = malloc(fileSize + 1);
    if (!buffer) {
        fclose(in);
        perror("Error allocating memory");
        return EXIT_FAILURE;
    }

    size_t bytesRead = fread(buffer, 1, fileSize, in);
    buffer[bytesRead] = '\0';

    unsigned int checksum = calculateChecksum(buffer, bytesRead);

    fclose(in);
    free(buffer);

    FILE *out = fopen(outputFile, "w");
    if (!out) {
        perror("Error opening output file");
        return EXIT_FAILURE;
    }

    fprintf(out, "%zu %u\n", bytesRead, checksum);

    fclose(out);

    return EXIT_SUCCESS;
}