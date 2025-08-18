#include <stdio.h>
#include <stdlib.h>

unsigned int calculate_checksum(const char *buffer, size_t length) {
    unsigned int checksum = 0;
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

    char *buffer = (char *)malloc(fileSize + 1);
    if (!buffer) {
        perror("Failed to allocate memory for buffer");
        fclose(inputFile);
        return EXIT_FAILURE;
    }

    fread(buffer, sizeof(char), fileSize, inputFile);
    fclose(inputFile);

    unsigned int checksum = calculate_checksum(buffer, fileSize);
    int isEmptyBuffer = (checksum == 0);

    FILE *outputFile = fopen("output.txt", "w");
    if (!outputFile) {
        perror("Failed to open output file");
        free(buffer);
        return EXIT_FAILURE;
    }

    fprintf(outputFile, "Number of bytes read: %zu\n", fileSize);
    fprintf(outputFile, "Checksum: %u\n", checksum);

    if (isEmptyBuffer) {
        fprintf(outputFile, "The buffer is empty.\n");
    } else {
        fprintf(outputFile, "The buffer is not empty.\n");
    }

    fclose(outputFile);
    free(buffer);

    return EXIT_SUCCESS;
}