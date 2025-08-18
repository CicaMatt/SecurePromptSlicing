#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

#define UPLOADS_DIR "uploads"
#define MAX_FILENAME_LENGTH 256

int main() {
    char filename[MAX_FILENAME_LENGTH];
    char filepath[MAX_FILENAME_LENGTH + sizeof(UPLOADS_DIR) + 2];
    FILE *sourceFile, *destinationFile;

    // Create uploads directory if it does not exist
    struct stat st = {0};
    if (stat(UPLOADS_DIR, &st) == -1) {
        mkdir(UPLOADS_DIR, 0755);
    }

    printf("Enter the name of the PDF file to upload: ");
    if (fgets(filename, sizeof(filename), stdin) != NULL) {
        // Remove newline character from filename
        size_t len = strlen(filename);
        if (len > 0 && filename[len - 1] == '\n') {
            filename[len - 1] = '\0';
        }
    }

    snprintf(filepath, sizeof(filepath), "%s/%s", UPLOADS_DIR, filename);

    sourceFile = fopen(filename, "rb");
    if (!sourceFile) {
        perror("Error opening file");
        return EXIT_FAILURE;
    }

    destinationFile = fopen(filepath, "wb");
    if (!destinationFile) {
        fclose(sourceFile);
        perror("Error creating file in uploads directory");
        return EXIT_FAILURE;
    }

    char buffer[4096];
    size_t bytesRead;
    while ((bytesRead = fread(buffer, 1, sizeof(buffer), sourceFile)) > 0) {
        fwrite(buffer, 1, bytesRead, destinationFile);
    }

    fclose(sourceFile);
    fclose(destinationFile);

    printf("File uploaded successfully to %s\n", filepath);

    return EXIT_SUCCESS;
}