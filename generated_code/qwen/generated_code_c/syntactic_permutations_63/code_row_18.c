#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *fileIn, *fileOut;
    char *buffer;
    long fileSize;

    fileIn = fopen("input.txt", "rb");
    if (fileIn == NULL) {
        perror("Error opening input file");
        return EXIT_FAILURE;
    }

    fseek(fileIn, 0, SEEK_END);
    fileSize = ftell(fileIn);
    rewind(fileIn);

    buffer = (char *)malloc(fileSize + 1);
    if (buffer == NULL) {
        perror("Memory allocation failed");
        fclose(fileIn);
        return EXIT_FAILURE;
    }

    size_t bytesRead = fread(buffer, 1, fileSize, fileIn);
    buffer[bytesRead] = '\0';

    fclose(fileIn);

    fileOut = fopen("output.txt", "w");
    if (fileOut == NULL) {
        perror("Error opening output file");
        free(buffer);
        return EXIT_FAILURE;
    }

    fprintf(fileOut, "%zu\n", bytesRead);

    fclose(fileOut);
    free(buffer);

    return EXIT_SUCCESS;
}