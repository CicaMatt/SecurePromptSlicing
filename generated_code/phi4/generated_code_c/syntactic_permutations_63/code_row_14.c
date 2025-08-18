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
        perror("Error opening output file");
        fclose(inputFile);
        return EXIT_FAILURE;
    }

    bytesRead = fread(buffer, 1, sizeof(buffer), inputFile);

    if (bytesRead == 0 && ferror(inputFile)) {
        fprintf(stderr, "Error reading input file\n");
        fclose(inputFile);
        fclose(outputFile);
        return EXIT_FAILURE;
    }

    if (feof(inputFile) && bytesRead == 0) {
        fputs("The buffer is empty.\n", outputFile);
    } else {
        printf("%zu bytes read from the buffer.\n", bytesRead);
        fprintf(outputFile, "%zu\n", bytesRead);
    }

    fclose(inputFile);
    fclose(outputFile);

    return EXIT_SUCCESS;
}