#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define UPLOADS_DIR "uploads/"
#define MAX_FILENAME_LENGTH 256

int main() {
    char filename[MAX_FILENAME_LENGTH];
    FILE *source, *destination;

    printf("Enter the name of the PDF file to upload: ");
    if (scanf("%s", filename) != 1) {
        fprintf(stderr, "Error reading filename.\n");
        return EXIT_FAILURE;
    }

    // Construct full path for source file
    char sourcePath[MAX_FILENAME_LENGTH + 5]; // +5 for ".pdf\0"
    snprintf(sourcePath, sizeof(sourcePath), "%s.pdf", filename);

    // Open the source PDF file in binary read mode
    source = fopen(sourcePath, "rb");
    if (!source) {
        perror("Error opening source file");
        return EXIT_FAILURE;
    }

    // Construct full path for destination file
    char destPath[MAX_FILENAME_LENGTH + sizeof(UPLOADS_DIR)];
    snprintf(destPath, sizeof(destPath), "%s%s", UPLOADS_DIR, filename);

    // Open the destination PDF file in binary write mode
    destination = fopen(destPath, "wb");
    if (!destination) {
        perror("Error opening destination file");
        fclose(source);
        return EXIT_FAILURE;
    }

    // Copy contents from source to destination
    char buffer[4096];
    size_t bytesRead;
    while ((bytesRead = fread(buffer, 1, sizeof(buffer), source)) > 0) {
        if (fwrite(buffer, 1, bytesRead, destination) != bytesRead) {
            fprintf(stderr, "Error writing to destination file.\n");
            fclose(source);
            fclose(destination);
            return EXIT_FAILURE;
        }
    }

    // Check for errors during reading
    if (ferror(source)) {
        fprintf(stderr, "Error reading from source file.\n");
        fclose(source);
        fclose(destination);
        return EXIT_FAILURE;
    }

    // Close both files
    fclose(source);
    fclose(destination);

    printf("File uploaded successfully to %s\n", destPath);
    return EXIT_SUCCESS;
}