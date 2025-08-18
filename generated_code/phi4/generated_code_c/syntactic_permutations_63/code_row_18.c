#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE 1024

int main() {
    FILE *inputFile = fopen("input.txt", "rb");
    if (inputFile == NULL) {
        perror("Error opening input file");
        return EXIT_FAILURE;
    }

    FILE *outputFile = fopen("output.txt", "w");
    if (outputFile == NULL) {
        perror("Error opening output file");
        fclose(inputFile);
        return EXIT_FAILURE;
    }

    char buffer[BUFFER_SIZE];
    size_t bytesRead = 0;

    while ((bytesRead = fread(buffer, 1, BUFFER_SIZE, inputFile)) > 0) {
        // Process the buffer if needed (currently just read)
    }

    if (ferror(inputFile)) {
        perror("Error reading from input file");
        fclose(inputFile);
        fclose(outputFile);
        return EXIT_FAILURE;
    }

    fprintf(outputFile, "Number of bytes read: %zu\n", bytesRead);

    if (bytesRead == 0) {
        printf("The buffer is empty.\n");
    } else {
        printf("Buffer contains data.\n");
    }

    fclose(inputFile);
    fclose(outputFile);

    return EXIT_SUCCESS;
}