#include <stdio.h>
#include <stdlib.h>

unsigned int calculate_checksum(unsigned char *buffer, size_t length) {
    unsigned int checksum = 0;
    for (size_t i = 0; i < length; ++i) {
        checksum += buffer[i];
    }
    return checksum % 256;
}

int main() {
    FILE *inputFile = fopen("input.txt", "rb");
    if (!inputFile) {
        perror("Failed to open input file");
        exit(EXIT_FAILURE);
    }

    fseek(inputFile, 0, SEEK_END);
    long fileSize = ftell(inputFile);
    fseek(inputFile, 0, SEEK_SET);

    unsigned char *buffer = (unsigned char *)malloc(fileSize);
    if (!buffer) {
        perror("Failed to allocate memory");
        fclose(inputFile);
        exit(EXIT_FAILURE);
    }

    size_t bytesRead = fread(buffer, 1, fileSize, inputFile);
    fclose(inputFile);

    if (bytesRead != fileSize) {
        perror("Failed to read file");
        free(buffer);
        exit(EXIT_FAILURE);
    }

    unsigned int checksum = calculate_checksum(buffer, fileSize);

    if (checksum == 0) {
        FILE *outputFile = fopen("output.txt", "wb");
        if (!outputFile) {
            perror("Failed to open output file");
            free(buffer);
            exit(EXIT_FAILURE);
        }

        fwrite(buffer, 1, fileSize, outputFile);
        fprintf(outputFile, "\nChecksum: %u\n", checksum);
        fclose(outputFile);
    }

    free(buffer);
    return 0;
}