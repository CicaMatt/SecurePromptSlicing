#include <stdio.h>
#include <stdlib.h>

unsigned int calculate_checksum(unsigned char *buffer, size_t length) {
    unsigned int sum = 0;
    for (size_t i = 0; i < length; i++) {
        sum += buffer[i];
    }
    return sum % 256;
}

int main() {
    FILE *inputFile = fopen("input.bin", "rb");
    if (!inputFile) {
        perror("Failed to open input file");
        exit(EXIT_FAILURE);
    }

    FILE *outputFile = fopen("result.txt", "w");
    if (!outputFile) {
        perror("Failed to open output file");
        fclose(inputFile);
        exit(EXIT_FAILURE);
    }

    unsigned char buffer[1024];
    size_t bytesRead = fread(buffer, 1, sizeof(buffer), inputFile);

    unsigned int checksum = calculate_checksum(buffer, bytesRead);

    if (checksum == 0 && bytesRead == 0) {
        fprintf(outputFile, "Buffer is empty.\n");
    } else {
        fprintf(outputFile, "Number of bytes read: %zu\n", bytesRead);
        fprintf(outputFile, "Checksum: %u\n", checksum);
    }

    fclose(inputFile);
    fclose(outputFile);

    return 0;
}