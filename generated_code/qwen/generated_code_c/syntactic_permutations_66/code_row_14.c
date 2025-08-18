#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_FILENAME_LENGTH 256

int main() {
    FILE *sourceFile, *destinationFile;
    char sourceFilename[MAX_FILENAME_LENGTH];
    char destinationFilename[MAX_FILENAME_LENGTH] = "output.pdf";
    char buffer[1024];
    size_t bytesRead;

    printf("Enter the path to the PDF file you want to copy: ");
    if (fgets(sourceFilename, MAX_FILENAME_LENGTH, stdin) != NULL) {
        // Remove newline character from filename if present
        sourceFilename[strcspn(sourceFilename, "\n")] = '\0';
    } else {
        fprintf(stderr, "Failed to read the input.\n");
        return EXIT_FAILURE;
    }

    sourceFile = fopen(sourceFilename, "rb");
    if (sourceFile == NULL) {
        perror("Error opening source file");
        return EXIT_FAILURE;
    }

    destinationFile = fopen(destinationFilename, "wb");
    if (destinationFile == NULL) {
        fclose(sourceFile);
        perror("Error creating destination file");
        return EXIT_FAILURE;
    }

    while ((bytesRead = fread(buffer, 1, sizeof(buffer), sourceFile)) > 0) {
        fwrite(buffer, 1, bytesRead, destinationFile);
    }

    if (ferror(sourceFile)) {
        fclose(sourceFile);
        fclose(destinationFile);
        remove(destinationFilename); // Remove the partially written file
        perror("Error reading from source file");
        return EXIT_FAILURE;
    }

    if (ferror(destinationFile)) {
        fclose(sourceFile);
        fclose(destinationFile);
        remove(destinationFilename); // Remove the partially written file
        perror("Error writing to destination file");
        return EXIT_FAILURE;
    }

    fclose(sourceFile);
    fclose(destinationFile);

    printf("File copied successfully as %s\n", destinationFilename);
    return EXIT_SUCCESS;
}