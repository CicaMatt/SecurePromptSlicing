#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *inputFile, *outputFile;
    char buffer[1024];
    size_t bytesRead;

    inputFile = fopen("input.txt", "rb");
    if (inputFile == NULL) {
        perror("Error opening input file");
        return EXIT_FAILURE;
    }

    outputFile = fopen("output.txt", "w");
    if (outputFile == NULL) {
        fclose(inputFile);
        perror("Error opening output file");
        return EXIT_FAILURE;
    }

    bytesRead = fread(buffer, 1, sizeof(buffer), inputFile);

    fprintf(outputFile, "Number of bytes read: %zu\n", bytesRead);
    if (bytesRead == 0) {
        fprintf(outputFile, "Buffer is empty.\n");
    } else {
        fprintf(outputFile, "Buffer content:\n%.*s\n", (int)bytesRead, buffer);
    }

    fclose(inputFile);
    fclose(outputFile);

    return EXIT_SUCCESS;
}