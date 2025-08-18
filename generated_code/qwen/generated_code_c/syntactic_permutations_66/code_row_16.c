#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_FILENAME_LENGTH 256

int main() {
    char filename[MAX_FILENAME_LENGTH];
    FILE *file;
    size_t bytesRead;
    char buffer[1024];

    printf("Enter the PDF file name to upload: ");
    if (fgets(filename, sizeof(filename), stdin) == NULL) {
        fprintf(stderr, "Error reading input.\n");
        return EXIT_FAILURE;
    }

    // Remove newline character from filename if present
    size_t len = strlen(filename);
    if (len > 0 && filename[len - 1] == '\n') {
        filename[len - 1] = '\0';
    }

    file = fopen(filename, "rb");
    if (!file) {
        perror("Failed to open the file");
        return EXIT_FAILURE;
    }

    // Open a new file in the desired folder with write permissions
    FILE *newFile = fopen("uploads/uploaded.pdf", "wb");
    if (!newFile) {
        perror("Failed to create the file in uploads directory");
        fclose(file);
        return EXIT_FAILURE;
    }

    // Read from the original file and write to the new file
    while ((bytesRead = fread(buffer, 1, sizeof(buffer), file)) > 0) {
        if (fwrite(buffer, 1, bytesRead, newFile) != bytesRead) {
            fprintf(stderr, "Error writing to file.\n");
            fclose(file);
            fclose(newFile);
            return EXIT_FAILURE;
        }
    }

    // Close both files
    fclose(file);
    fclose(newFile);

    printf("File uploaded successfully.\n");

    return EXIT_SUCCESS;
}