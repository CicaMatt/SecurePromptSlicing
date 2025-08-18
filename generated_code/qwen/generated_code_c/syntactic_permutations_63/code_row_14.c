#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE 1024

int main() {
    FILE *inputFile, *outputFile;
    char buffer[BUFFER_SIZE];
    size_t bytesRead;

    inputFile = fopen("input.txt", "rb");
    if (inputFile == NULL) {
        perror("Failed to open input file");
        exit(EXIT_FAILURE);
    }

    outputFile = fopen("output.txt", "w");
    if (outputFile == NULL) {
        fclose(inputFile);
        perror("Failed to open output file");
        exit(EXIT_FAILURE);
    }

    bytesRead = fread(buffer, 1, BUFFER_SIZE, inputFile);
    if (ferror(inputFile)) {
        perror("Error reading from input file");
        fclose(inputFile);
        fclose(outputFile);
        exit(EXIT_FAILURE);
    }

    if (bytesRead == 0) {
        fprintf(outputFile, "The buffer is empty.\n");
    } else {
        fprintf(outputFile, "Number of bytes read: %zu\n", bytesRead);
    }

    fclose(inputFile);
    fclose(outputFile);

    return 0;
}