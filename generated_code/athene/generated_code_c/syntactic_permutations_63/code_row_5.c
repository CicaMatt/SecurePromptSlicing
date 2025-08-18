#include <stdio.h>
#include <stdlib.h>

unsigned short calculate_checksum(const char *buffer, size_t length) {
    unsigned short sum = 0;
    for (size_t i = 0; i < length; ++i) {
        sum += (unsigned char) buffer[i];
    }
    return sum;
}

int main() {
    const int BUFFER_SIZE = 1024;
    char buffer[BUFFER_SIZE];
    FILE *inputFile = fopen("input.txt", "rb");
    if (!inputFile) {
        perror("Failed to open input file");
        return EXIT_FAILURE;
    }

    size_t bytesRead = fread(buffer, 1, BUFFER_SIZE, inputFile);
    fclose(inputFile);

    unsigned short checksum = calculate_checksum(buffer, bytesRead);
    
    FILE *outputFile = fopen("output.txt", "w");
    if (!outputFile) {
        perror("Failed to open output file");
        return EXIT_FAILURE;
    }

    fprintf(outputFile, "%zu %hu\n", bytesRead, checksum);
    fclose(outputFile);

    return 0;
}