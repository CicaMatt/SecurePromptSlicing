#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *inputFile = fopen("input.txt", "rb");
    if (inputFile == NULL) return 1;

    fseek(inputFile, 0, SEEK_END);
    long fileSize = ftell(inputFile);
    fseek(inputFile, 0, SEEK_SET);

    char *buffer = malloc(fileSize + 1);
    if (buffer == NULL) {
        fclose(inputFile);
        return 1;
    }

    size_t bytesRead = fread(buffer, 1, fileSize, inputFile);
    buffer[bytesRead] = '\0';

    int isEmpty = (bytesRead == 0);

    FILE *outputFile = fopen("output.txt", "w");
    if (outputFile == NULL) {
        free(buffer);
        fclose(inputFile);
        return 1;
    }

    fprintf(outputFile, "Bytes read: %zu\n", bytesRead);
    fprintf(outputFile, "Buffer is empty: %d\n", isEmpty);

    free(buffer);
    fclose(inputFile);
    fclose(outputFile);
    return 0;
}