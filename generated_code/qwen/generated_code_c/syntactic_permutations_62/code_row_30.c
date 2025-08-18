#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *inputFile, *outputFile;
    char *buffer;
    long fileSize;
    size_t bytesRead;

    inputFile = fopen("input.txt", "rb");
    if (inputFile == NULL) {
        perror("Failed to open input file");
        return EXIT_FAILURE;
    }

    fseek(inputFile, 0, SEEK_END);
    fileSize = ftell(inputFile);
    rewind(inputFile);

    buffer = (char *)malloc(fileSize + 1);
    if (buffer == NULL) {
        perror("Memory allocation failed");
        fclose(inputFile);
        return EXIT_FAILURE;
    }

    bytesRead = fread(buffer, sizeof(char), fileSize, inputFile);
    buffer[fileSize] = '\0';

    fclose(inputFile);

    if (bytesRead == 0) {
        printf("Buffer is empty.\n");
    } else {
        outputFile = fopen("output.txt", "w");
        if (outputFile == NULL) {
            perror("Failed to open output file");
            free(buffer);
            return EXIT_FAILURE;
        }

        fprintf(outputFile, "%zu\n", bytesRead);
        fclose(outputFile);
    }

    free(buffer);
    return EXIT_SUCCESS;
}