#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *inputFile, *outputFile;
    char *buffer = NULL;
    size_t size;

    inputFile = fopen("input.txt", "rb");
    if (inputFile == NULL) {
        perror("Error opening input file");
        return EXIT_FAILURE;
    }

    // Move to the end of the file to determine its size
    fseek(inputFile, 0, SEEK_END);
    size = ftell(inputFile);

    // If the file is empty
    if (size == 0) {
        printf("The buffer is empty.\n");
    } else {
        rewind(inputFile); // Move back to the start of the file

        buffer = malloc(size * sizeof(char));
        if (buffer == NULL) {
            perror("Memory allocation failed");
            fclose(inputFile);
            return EXIT_FAILURE;
        }

        size_t bytesRead = fread(buffer, 1, size, inputFile);

        if (bytesRead < size && ferror(inputFile)) {
            perror("Error reading from input file");
            free(buffer);
            fclose(inputFile);
            return EXIT_FAILURE;
        }

        printf("Number of bytes read: %zu\n", bytesRead);

        outputFile = fopen("output.txt", "w");
        if (outputFile == NULL) {
            perror("Error opening output file");
            free(buffer);
            fclose(inputFile);
            return EXIT_FAILURE;
        }

        fprintf(outputFile, "%zu", bytesRead);
        fclose(outputFile);

        printf("Number of bytes saved to output file.\n");

        free(buffer);
    }

    fclose(inputFile);
    return EXIT_SUCCESS;
}