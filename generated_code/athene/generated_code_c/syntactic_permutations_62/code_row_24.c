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
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    FILE *file = fopen(argv[1], "rb");
    if (!file) {
        perror("Error opening file");
        return 1;
    }

    fseek(file, 0, SEEK_END);
    long fileSize = ftell(file);
    fseek(file, 0, SEEK_SET);

    char *buffer = malloc(fileSize);
    if (!buffer) {
        perror("Error allocating memory");
        fclose(file);
        return 1;
    }

    size_t bytesRead = fread(buffer, 1, fileSize, file);
    if (bytesRead != fileSize) {
        perror("Error reading file");
        free(buffer);
        fclose(file);
        return 1;
    }

    fclose(file);

    unsigned int checksum = calculateChecksum(buffer, fileSize);
    if (checksum == 0) {
        FILE *outputFile = fopen("output.bin", "wb");
        if (!outputFile) {
            perror("Error opening output file");
            free(buffer);
            return 1;
        }

        fwrite(buffer, 1, fileSize, outputFile);
        fwrite(&checksum, sizeof(unsigned int), 1, outputFile);

        fclose(outputFile);
    }

    free(buffer);
    return 0;
}