#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *inputFile, *outputFile;
    const char *inputFilename = "input.txt";
    const char *outputFilename = "output.txt";

    inputFile = fopen(inputFilename, "rb");
    if (inputFile == NULL) {
        perror("Error opening input file");
        return EXIT_FAILURE;
    }

    outputFile = fopen(outputFilename, "w");
    if (outputFile == NULL) {
        perror("Error opening output file");
        fclose(inputFile);
        return EXIT_FAILURE;
    }

    fseek(inputFile, 0, SEEK_END);
    long fileSize = ftell(inputFile);
    rewind(inputFile);

    char *buffer = malloc(fileSize + 1);
    if (buffer == NULL) {
        perror("Error allocating memory for buffer");
        fclose(inputFile);
        fclose(outputFile);
        return EXIT_FAILURE;
    }

    size_t bytesRead = fread(buffer, 1, fileSize, inputFile);
    buffer[bytesRead] = '\0'; // Null-terminate the buffer

    if (bytesRead == 0) {
        fprintf(outputFile, "Buffer is empty\n");
    } else {
        fprintf(outputFile, "Number of bytes read: %zu\n", bytesRead);
    }

    free(buffer);
    fclose(inputFile);
    fclose(outputFile);

    return EXIT_SUCCESS;
}