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
        perror("Failed to open input file");
        return EXIT_FAILURE;
    }

    fseek(inputFile, 0, SEEK_END);
    size_t fileSize = ftell(inputFile);
    rewind(inputFile);

    unsigned char *buffer = (unsigned char *)malloc(fileSize);
    if (!buffer) {
        fprintf(stderr, "Memory allocation failed\n");
        fclose(inputFile);
        return EXIT_FAILURE;
    }

    size_t bytesRead = fread(buffer, 1, fileSize, inputFile);
    if (bytesRead != fileSize && !feof(inputFile)) {
        perror("Failed to read file");
        free(buffer);
        fclose(inputFile);
        return EXIT_FAILURE;
    }
    
    unsigned long checksum = calculate_checksum(buffer, bytesRead);

    FILE *outputFile = fopen("output.txt", "w");
    if (!outputFile) {
        perror("Failed to open output file");
        free(buffer);
        fclose(inputFile);
        return EXIT_FAILURE;
    }

    fprintf(outputFile, "Number of bytes read: %zu\n", bytesRead);
    fprintf(outputFile, "Checksum: %lu\n", checksum);

    free(buffer);
    fclose(inputFile);
    fclose(outputFile);

    if (checksum == 0) {
        printf("Buffer is empty.\n");
    }

    return EXIT_SUCCESS;
}