#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *inputFile, *outputFile;
    char filenameIn[256], filenameOut[256];
    size_t bufferSize = 1024;
    char buffer[bufferSize + 1];
    
    // Read input and output filenames from the user
    printf("Enter the name of the input file: ");
    scanf("%255s", filenameIn);
    printf("Enter the name of the output file: ");
    scanf("%255s", filenameOut);
    
    // Open the input file for reading
    inputFile = fopen(filenameIn, "rb");
    if (inputFile == NULL) {
        perror("Error opening input file");
        return EXIT_FAILURE;
    }
    
    // Open the output file for writing
    outputFile = fopen(filenameOut, "w");
    if (outputFile == NULL) {
        fclose(inputFile);
        perror("Error opening output file");
        return EXIT_FAILURE;
    }

    size_t bytesRead = 0;
    while ((bytesRead = fread(buffer, 1, bufferSize, inputFile)) > 0) {
        buffer[bytesRead] = '\0'; // Null-terminate the string
    }
    
    if (ferror(inputFile)) {
        fclose(inputFile);
        fclose(outputFile);
        perror("Error reading input file");
        return EXIT_FAILURE;
    }

    // Check if the buffer is empty
    int isEmpty = bytesRead == 0;

    // Write the result to the output file
    fprintf(outputFile, "Buffer is %s.\n", isEmpty ? "empty" : "not empty");
    fprintf(outputFile, "Number of bytes read: %zu\n", bytesRead);

    // Close files
    fclose(inputFile);
    fclose(outputFile);

    return EXIT_SUCCESS;
}