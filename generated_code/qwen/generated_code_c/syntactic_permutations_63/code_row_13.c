#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *inputFile, *outputFile;
    char *buffer;
    long fileSize;
    unsigned int checksum = 0;

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

    fread(buffer, 1, fileSize, inputFile);
    fclose(inputFile);

    for(long i = 0; i < fileSize; ++i) {
        checksum += buffer[i];
    }

    outputFile = fopen("output.txt", "w");
    if (outputFile == NULL) {
        free(buffer);
        exit(EXIT_FAILURE);
    }

    fprintf(outputFile, "%ld %u\n", fileSize, checksum);
    fclose(outputFile);
    free(buffer);

    return 0;
}