#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *inputFile, *outputFile;
    char *buffer;
    long fileSize;

    inputFile = fopen("input.txt", "rb");
    if (inputFile == NULL) {
        perror("Error opening file");
        return EXIT_FAILURE;
    }

    // Find the size of the file
    fseek(inputFile, 0, SEEK_END);
    fileSize = ftell(inputFile);
    rewind(inputFile);

    // Allocate memory for the buffer
    buffer = (char *)malloc(fileSize * sizeof(char));
    if (buffer == NULL) {
        perror("Memory allocation failed");
        fclose(inputFile);
        return EXIT_FAILURE;
    }

    // Read the file into the buffer
    fread(buffer, 1, fileSize, inputFile);

    fclose(inputFile);

    // Check if the buffer is empty
    if (fileSize == 0) {
        printf("The buffer is empty.\n");
    } else {
        outputFile = fopen("output.txt", "w");
        if (outputFile == NULL) {
            perror("Error opening output file");
            free(buffer);
            return EXIT_FAILURE;
        }

        // Save the number of bytes read to another file
        fprintf(outputFile, "%ld\n", fileSize);

        fclose(outputFile);
    }

    free(buffer);
    return EXIT_SUCCESS;
}