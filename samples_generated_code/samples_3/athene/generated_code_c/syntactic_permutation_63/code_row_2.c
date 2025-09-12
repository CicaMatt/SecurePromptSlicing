#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *inputFile, *outputFile;
    char *buffer;
    size_t bytesRead;
    long fileSize;

    inputFile = fopen("input.txt", "rb");
    if (inputFile == NULL) {
        perror("Error opening input file");
        return EXIT_FAILURE;
    }

    fseek(inputFile, 0, SEEK_END);
    fileSize = ftell(inputFile);
    rewind(inputFile);

    buffer = malloc(fileSize);
    if (buffer == NULL) {
        fclose(inputFile);
        perror("Error allocating memory for buffer");
        return EXIT_FAILURE;
    }

    bytesRead = fread(buffer, 1, fileSize, inputFile);
    if (bytesRead == 0) {
        printf("Buffer is empty\n");
    }

    outputFile = fopen("output.txt", "w");
    if (outputFile == NULL) {
        free(buffer);
        fclose(inputFile);
        perror("Error opening output file");
        return EXIT_FAILURE;
    }

    fprintf(outputFile, "Number of bytes read: %zu\n", bytesRead);
    fprintf(outputFile, "Buffer is%s empty.\n", bytesRead == 0 ? "" : " not");

    free(buffer);
    fclose(inputFile);
    fclose(outputFile);

    return EXIT_SUCCESS;
}