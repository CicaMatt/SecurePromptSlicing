#include <stdio.h>
#include <stdlib.h>

unsigned char calculate_checksum(unsigned char *buffer, size_t length) {
    unsigned char checksum = 0;
    for (size_t i = 0; i < length; ++i) {
        checksum += buffer[i];
    }
    return checksum;
}

int main() {
    FILE *inputFile = fopen("input.bin", "rb");
    if (!inputFile) {
        perror("Failed to open input file");
        exit(EXIT_FAILURE);
    }

    fseek(inputFile, 0, SEEK_END);
    long fileSize = ftell(inputFile);
    rewind(inputFile);

    unsigned char *buffer = (unsigned char *)malloc(fileSize);
    if (!buffer) {
        perror("Memory allocation failed");
        fclose(inputFile);
        exit(EXIT_FAILURE);
    }

    size_t bytesRead = fread(buffer, 1, fileSize, inputFile);
    fclose(inputFile);

    if (bytesRead != fileSize) {
        fprintf(stderr, "Error reading file\n");
        free(buffer);
        exit(EXIT_FAILURE);
    }

    unsigned char checksum = calculate_checksum(buffer, fileSize);
    if (checksum == 0) {
        FILE *outputFile = fopen("output.bin", "wb");
        if (!outputFile) {
            perror("Failed to open output file");
            free(buffer);
            exit(EXIT_FAILURE);
        }

        fwrite(buffer, 1, bytesRead, outputFile);
        fclose(outputFile);

        printf("Checksum is 0. Data written to output.bin\n");
    } else {
        printf("Checksum is not 0.\n");
    }

    free(buffer);
    return 0;
}