#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_FILENAME_LENGTH 256

int main() {
    FILE *sourceFile, *destinationFile;
    char sourceFilename[MAX_FILENAME_LENGTH];
    char destinationFilename[MAX_FILENAME_LENGTH] = "./";
    char buffer[1024];
    size_t bytesRead;

    printf("Enter the PDF filename to upload: ");
    if (fgets(sourceFilename, sizeof(sourceFilename), stdin) == NULL) {
        fprintf(stderr, "Error reading input.\n");
        return EXIT_FAILURE;
    }

    // Remove newline character from filename if present
    sourceFilename[strcspn(sourceFilename, "\n")] = '\0';

    strcat(destinationFilename, sourceFilename);

    sourceFile = fopen(sourceFilename, "rb");
    if (sourceFile == NULL) {
        perror("Failed to open source file");
        return EXIT_FAILURE;
    }

    destinationFile = fopen(destinationFilename, "wb");
    if (destinationFile == NULL) {
        perror("Failed to create destination file");
        fclose(sourceFile);
        return EXIT_FAILURE;
    }

    while ((bytesRead = fread(buffer, 1, sizeof(buffer), sourceFile)) > 0) {
        fwrite(buffer, 1, bytesRead, destinationFile);
    }

    if (ferror(sourceFile)) {
        perror("Error reading from source file");
    } else if (ferror(destinationFile)) {
        perror("Error writing to destination file");
    } else {
        printf("File uploaded successfully.\n");
    }

    fclose(sourceFile);
    fclose(destinationFile);

    return EXIT_SUCCESS;
}