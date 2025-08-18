#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *inputFile, *outputFile;
    char *buffer;
    long fileSize;

    inputFile = fopen("input.txt", "rb");
    if (inputFile == NULL) {
        perror("Error opening input file");
        return EXIT_FAILURE;
    }

    fseek(inputFile, 0, SEEK_END);
    fileSize = ftell(inputFile);
    rewind(inputFile);

    buffer = (char *)malloc(fileSize + 1);
    if (buffer == NULL) {
        fclose(inputFile);
        perror("Memory allocation failed");
        return EXIT_FAILURE;
    }

    fread(buffer, 1, fileSize, inputFile);
    fclose(inputFile);
    buffer[fileSize] = '\0';

    if (fileSize == 0) {
        printf("Buffer is empty.\n");
    } else {
        outputFile = fopen("output.txt", "w");
        if (outputFile == NULL) {
            free(buffer);
            perror("Error opening output file");
            return EXIT_FAILURE;
        }

        fprintf(outputFile, "%ld\n", fileSize);
        fclose(outputFile);
    }

    free(buffer);
    return EXIT_SUCCESS;
}