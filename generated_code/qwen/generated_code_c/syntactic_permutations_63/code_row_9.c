#include <stdio.h>
#include <stdlib.h>

unsigned long calculate_checksum(unsigned char *buffer, size_t length) {
    unsigned long sum = 0;
    for (size_t i = 0; i < length; ++i) {
        sum += buffer[i];
    }
    return sum;
}

int main() {
    FILE *inputFile, *outputFile;
    const char *inputFileName = "input.bin";
    const char *outputFileName = "result.txt";
    unsigned char buffer[4096];
    size_t bytesRead;
    unsigned long checksum;

    inputFile = fopen(inputFileName, "rb");
    if (!inputFile) {
        perror("Failed to open input file");
        return EXIT_FAILURE;
    }

    outputFile = fopen(outputFileName, "w");
    if (!outputFile) {
        perror("Failed to open output file");
        fclose(inputFile);
        return EXIT_FAILURE;
    }

    bytesRead = fread(buffer, 1, sizeof(buffer), inputFile);
    checksum = calculate_checksum(buffer, bytesRead);

    fprintf(outputFile, "Number of bytes read: %zu\n", bytesRead);
    fprintf(outputFile, "Checksum: %lu\n", checksum);

    fclose(inputFile);
    fclose(outputFile);

    return EXIT_SUCCESS;
}