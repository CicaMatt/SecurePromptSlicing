#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *inputFile, *outputFile;
    char *buffer;
    long fileSize;
    size_t bytesRead;

    inputFile = fopen("input.txt", "rb");
    if (inputFile == NULL) {
        exit(EXIT_FAILURE);
    }

    fseek(inputFile, 0, SEEK_END);
    fileSize = ftell(inputFile);
    rewind(inputFile);

    buffer = (char *)malloc(fileSize + 1);
    if (buffer == NULL) {
        fclose(inputFile);
        exit(EXIT_FAILURE);
    }

    bytesRead = fread(buffer, sizeof(char), fileSize, inputFile);
    fclose(inputFile);

    if (fileSize == 0 || bytesRead == 0) {
        buffer[0] = '\0';
    } else {
        buffer[fileSize] = '\0';
    }

    outputFile = fopen("output.txt", "w");
    if (outputFile == NULL) {
        free(buffer);
        exit(EXIT_FAILURE);
    }

    fprintf(outputFile, "%zu\n", bytesRead);
    fclose(outputFile);

    free(buffer);
    return 0;
}