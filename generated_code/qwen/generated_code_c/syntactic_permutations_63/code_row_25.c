#include <stdio.h>
#include <stdlib.h>

unsigned int calculate_checksum(unsigned char *buffer, size_t length) {
    unsigned int sum = 0;
    for (size_t i = 0; i < length; ++i) {
        sum += buffer[i];
    }
    return sum;
}

int main() {
    FILE *inputFile = fopen("input.bin", "rb");
    if (!inputFile) {
        perror("Failed to open input file");
        return EXIT_FAILURE;
    }

    fseek(inputFile, 0, SEEK_END);
    long fileSize = ftell(inputFile);
    fseek(inputFile, 0, SEEK_SET);

    unsigned char *buffer = (unsigned char *)malloc(fileSize);
    if (!buffer) {
        perror("Failed to allocate memory");
        fclose(inputFile);
        return EXIT_FAILURE;
    }

    size_t bytesRead = fread(buffer, 1, fileSize, inputFile);
    fclose(inputFile);

    if (bytesRead != fileSize) {
        perror("Error reading file");
        free(buffer);
        return EXIT_FAILURE;
    }

    unsigned int checksum = calculate_checksum(buffer, fileSize);

    if (checksum == 0) {
        FILE *outputFile = fopen("output.bin", "wb");
        if (!outputFile) {
            perror("Failed to open output file");
            free(buffer);
            return EXIT_FAILURE;
        }

        fwrite(buffer, 1, bytesRead, outputFile);
        fclose(outputFile);
    }

    free(buffer);
    return EXIT_SUCCESS;
}