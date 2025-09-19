#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define UPLOADS_DIR "uploads/"
#define MAX_FILENAME_LENGTH 256

int main() {
    char filename[MAX_FILENAME_LENGTH];
    FILE *sourceFile, *destinationFile;
    
    printf("Enter the path to the PDF file you want to upload: ");
    if (fgets(filename, sizeof(filename), stdin) == NULL) {
        fprintf(stderr, "Error reading input.\n");
        return EXIT_FAILURE;
    }
    
    // Remove newline character from filename
    size_t len = strlen(filename);
    if (len > 0 && filename[len - 1] == '\n') {
        filename[len - 1] = '\0';
    }

    sourceFile = fopen(filename, "rb");
    if (!sourceFile) {
        perror("Failed to open the file");
        return EXIT_FAILURE;
    }

    // Extract the base name of the file
    char *baseName = strrchr(filename, '/');
    if (baseName != NULL) {
        baseName++;
    } else {
        baseName = filename;
    }

    char destinationPath[MAX_FILENAME_LENGTH];
    snprintf(destinationPath, sizeof(destinationPath), "%s%s", UPLOADS_DIR, baseName);

    destinationFile = fopen(destinationPath, "wb");
    if (!destinationFile) {
        perror("Failed to create the file in uploads directory");
        fclose(sourceFile);
        return EXIT_FAILURE;
    }

    char buffer[4096];
    size_t bytesRead;
    while ((bytesRead = fread(buffer, 1, sizeof(buffer), sourceFile)) > 0) {
        if (fwrite(buffer, 1, bytesRead, destinationFile) != bytesRead) {
            perror("Failed to write to the file in uploads directory");
            fclose(sourceFile);
            fclose(destinationFile);
            return EXIT_FAILURE;
        }
    }

    fclose(sourceFile);
    fclose(destinationFile);

    printf("File uploaded successfully to %s\n", destinationPath);

    return EXIT_SUCCESS;
}