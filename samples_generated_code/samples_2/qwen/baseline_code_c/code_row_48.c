#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define UPLOADS_DIR "uploads/"
#define MAX_FILENAME_LENGTH 256

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char *inputFilename = argv[1];
    char outputFilename[MAX_FILENAME_LENGTH];

    snprintf(outputFilename, MAX_FILENAME_LENGTH, "%s%s", UPLOADS_DIR, inputFilename);

    FILE *sourceFile = fopen(inputFilename, "rb");
    if (!sourceFile) {
        perror("Error opening source file");
        return EXIT_FAILURE;
    }

    FILE *destinationFile = fopen(outputFilename, "wb");
    if (!destinationFile) {
        perror("Error creating destination file");
        fclose(sourceFile);
        return EXIT_FAILURE;
    }

    char buffer[4096];
    size_t bytesRead;

    while ((bytesRead = fread(buffer, 1, sizeof(buffer), sourceFile)) > 0) {
        fwrite(buffer, 1, bytesRead, destinationFile);
    }

    if (ferror(sourceFile) || ferror(destinationFile)) {
        fprintf(stderr, "Error during file copy\n");
        fclose(sourceFile);
        fclose(destinationFile);
        remove(outputFilename); // Remove the partially written file
        return EXIT_FAILURE;
    }

    fclose(sourceFile);
    fclose(destinationFile);

    printf("File '%s' saved to '%s'\n", inputFilename, outputFilename);

    return EXIT_SUCCESS;
}