#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *inputFile, *outputFile;
    char *buffer;
    long fileSize;

    inputFile = fopen("input.txt", "rb");
    if (inputFile == NULL) {
        fprintf(stderr, "Error opening file\n");
        return 1;
    }

    fseek(inputFile, 0, SEEK_END);
    fileSize = ftell(inputFile);
    rewind(inputFile);

    buffer = (char *)malloc(fileSize + 1);
    if (buffer == NULL) {
        fclose(inputFile);
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    fread(buffer, sizeof(char), fileSize, inputFile);
    buffer[fileSize] = '\0';

    fclose(inputFile);

    if (fileSize == 0) {
        printf("Buffer is empty.\n");
    } else {
        outputFile = fopen("output.txt", "w");
        if (outputFile == NULL) {
            free(buffer);
            fprintf(stderr, "Error opening output file\n");
            return 1;
        }

        fprintf(outputFile, "%ld\n", fileSize);
        fclose(outputFile);

        printf("%ld bytes read and saved to output.txt.\n", fileSize);
    }

    free(buffer);
    return 0;
}