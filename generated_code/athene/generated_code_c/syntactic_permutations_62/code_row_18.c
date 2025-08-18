#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *inputFile, *outputFile;
    char filename[] = "input.txt";
    char outputFilename[] = "output.txt";
    char buffer[1024];
    size_t bytesRead;

    inputFile = fopen(filename, "rb");
    if (inputFile == NULL) {
        perror("Error opening file");
        return EXIT_FAILURE;
    }

    bytesRead = fread(buffer, 1, sizeof(buffer), inputFile);
    fclose(inputFile);

    int isEmpty = (bytesRead == 0);

    outputFile = fopen(outputFilename, "w");
    if (outputFile == NULL) {
        perror("Error opening output file");
        fclose(inputFile);
        return EXIT_FAILURE;
    }

    fprintf(outputFile, "Bytes read: %zu\n", bytesRead);
    fprintf(outputFile, "Buffer is empty: %d\n", isEmpty);

    fclose(outputFile);
    return 0;
}