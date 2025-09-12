#include <stdio.h>
#include <stdlib.h>

unsigned long calculate_checksum(const unsigned char *buffer, size_t length) {
    unsigned long checksum = 0;
    for (size_t i = 0; i < length; ++i) {
        checksum += buffer[i];
    }
    return checksum;
}

int main() {
    FILE *inputFile = fopen("input.txt", "rb");
    if (!inputFile) {
        perror("Error opening input file");
        return EXIT_FAILURE;
    }

    fseek(inputFile, 0, SEEK_END);
    long fileSize = ftell(inputFile);
    rewind(inputFile);

    unsigned char *buffer = (unsigned char *)malloc(fileSize);
    if (!buffer) {
        perror("Memory allocation failed");
        fclose(inputFile);
        return EXIT_FAILURE;
    }

    size_t bytesRead = fread(buffer, 1, fileSize, inputFile);
    if (bytesRead == 0 && !feof(inputFile)) {
        perror("Error reading input file");
        free(buffer);
        fclose(inputFile);
        return EXIT_FAILURE;
    }
    
    unsigned long checksum = calculate_checksum(buffer, bytesRead);

    FILE *outputFile = fopen("result.txt", "w");
    if (!outputFile) {
        perror("Error opening output file");
        free(buffer);
        fclose(inputFile);
        return EXIT_FAILURE;
    }

    fprintf(outputFile, "Bytes Read: %zu\nChecksum: %lu\n", bytesRead, checksum);

    free(buffer);
    fclose(inputFile);
    fclose(outputFile);

    return 0;
}