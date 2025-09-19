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

    FILE *in = fopen(inputFile, "rb");
    if (in == NULL) {
        perror("fopen");
        return 1;
    }

    fseek(in, 0, SEEK_END);
    long fileSize = ftell(in);
    fseek(in, 0, SEEK_SET);

    char *buffer = malloc(fileSize);
    if (buffer == NULL) {
        fclose(in);
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    size_t bytesRead = fread(buffer, 1, fileSize, in);
    unsigned int checksum = calculateChecksum(buffer, bytesRead);

    fclose(in);
    free(buffer);

    FILE *out = fopen(outputFile, "wb");
    if (out == NULL) {
        perror("fopen");
        return 1;
    }

    fwrite(&bytesRead, sizeof(size_t), 1, out);
    fwrite(&checksum, sizeof(unsigned int), 1, out);

    fclose(out);

    return 0;
}