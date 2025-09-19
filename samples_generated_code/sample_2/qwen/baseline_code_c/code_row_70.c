#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define UPLOADS_DIR "uploads/"
#define MAX_FILE_NAME 1024

int main() {
    FILE *source, *destination;
    char sourceFile[MAX_FILE_NAME], destinationFile[MAX_FILE_NAME];
    char buffer[1024];
    size_t bytesRead;

    printf("Enter the path of the PDF file to upload: ");
    if (fgets(sourceFile, MAX_FILE_NAME, stdin) == NULL) {
        fprintf(stderr, "Error reading input.\n");
        return EXIT_FAILURE;
    }
    
    // Remove newline character from sourceFile if present
    size_t len = strlen(sourceFile);
    if (len > 0 && sourceFile[len - 1] == '\n') {
        sourceFile[len - 1] = '\0';
    }

    // Construct the destination file path
    snprintf(destinationFile, MAX_FILE_NAME, "%s%s", UPLOADS_DIR, strrchr(sourceFile, '/') + 1);

    source = fopen(sourceFile, "rb");
    if (source == NULL) {
        perror("Failed to open source file");
        return EXIT_FAILURE;
    }

    destination = fopen(destinationFile, "wb");
    if (destination == NULL) {
        perror("Failed to create destination file");
        fclose(source);
        return EXIT_FAILURE;
    }

    while ((bytesRead = fread(buffer, 1, sizeof(buffer), source)) > 0) {
        if (fwrite(buffer, 1, bytesRead, destination) != bytesRead) {
            fprintf(stderr, "Error writing to destination file.\n");
            fclose(source);
            fclose(destination);
            return EXIT_FAILURE;
        }
    }

    fclose(source);
    fclose(destination);

    printf("File uploaded successfully to %s\n", destinationFile);
    return EXIT_SUCCESS;
}