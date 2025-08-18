#include <stdio.h>
#include <stdlib.h>

unsigned long calculate_checksum(const unsigned char *data, size_t length) {
    unsigned long checksum = 0;
    for (size_t i = 0; i < length; ++i) {
        checksum += data[i];
    }
    return checksum;
}

int main() {
    FILE *inputFile = fopen("input.txt", "rb");
    if (!inputFile) {
        perror("Failed to open input file");
        return EXIT_FAILURE;
    }

    fseek(inputFile, 0, SEEK_END);
    size_t fileSize = ftell(inputFile);
    rewind(inputFile);

    unsigned char *buffer = (unsigned char *)malloc(fileSize);
    if (!buffer) {
        perror("Memory allocation failed");
        fclose(inputFile);
        return EXIT_FAILURE;
    }

    size_t bytesRead = fread(buffer, 1, fileSize, inputFile);
    if (bytesRead != fileSize && !feof(inputFile)) {
        perror("Failed to read the entire file");
        free(buffer);
        fclose(inputFile);
        return EXIT_FAILURE;
    }
    fclose(inputFile);

    unsigned long checksum = calculate_checksum(buffer, bytesRead);
    int isBufferEmpty = (checksum == 0);

    FILE *outputFile = fopen("output.txt", "w");
    if (!outputFile) {
        perror("Failed to open output file");
        free(buffer);
        return EXIT_FAILURE;
    }

    fprintf(outputFile, "Bytes read: %zu\nChecksum: %lu\nBuffer empty: %s\n",
            bytesRead, checksum, isBufferEmpty ? "Yes" : "No");

    fclose(outputFile);
    free(buffer);

    return EXIT_SUCCESS;
}