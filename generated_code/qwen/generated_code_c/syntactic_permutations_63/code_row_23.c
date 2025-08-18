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
    FILE *inputFile, *outputFile;
    const char *inputFileName = "input.txt";
    const char *outputFileName = "output.txt";
    unsigned char *buffer;
    long fileLength;

    inputFile = fopen(inputFileName, "rb");
    if (!inputFile) {
        perror("Failed to open input file");
        return EXIT_FAILURE;
    }

    fseek(inputFile, 0, SEEK_END);
    fileLength = ftell(inputFile);
    fseek(inputFile, 0, SEEK_SET);

    buffer = (unsigned char *)malloc(fileLength + 1);
    if (!buffer) {
        perror("Memory allocation failed");
        fclose(inputFile);
        return EXIT_FAILURE;
    }

    fread(buffer, 1, fileLength, inputFile);
    fclose(inputFile);

    unsigned int checksum = calculate_checksum(buffer, fileLength);

    if (checksum == 0) {
        outputFile = fopen(outputFileName, "wb");
        if (!outputFile) {
            perror("Failed to open output file");
            free(buffer);
            return EXIT_FAILURE;
        }

        fwrite(buffer, 1, fileLength, outputFile);
        fprintf(outputFile, "\nChecksum: %u", checksum);
        fclose(outputFile);
    }

    free(buffer);
    return EXIT_SUCCESS;
}