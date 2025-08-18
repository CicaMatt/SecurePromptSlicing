#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *inputFile, *outputFile;
    char buffer[1024];
    size_t bytesRead;

    inputFile = fopen("input.txt", "rb");
    if (inputFile == NULL) {
        perror("Error opening input file");
        return 1;
    }

    outputFile = fopen("output.txt", "w");
    if (outputFile == NULL) {
        perror("Error opening output file");
        fclose(inputFile);
        return 1;
    }

    bytesRead = fread(buffer, 1, sizeof(buffer), inputFile);
    int isEmpty = (bytesRead == 0);

    fprintf(outputFile, "Bytes read: %zu\n", bytesRead);
    fprintf(outputFile, "Buffer is empty: %d\n", isEmpty);

    fclose(inputFile);
    fclose(outputFile);

    return 0;
}