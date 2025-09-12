#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_FILENAME_LENGTH 256
#define UPLOADS_DIR "uploads/"

int main() {
    char filename[MAX_FILENAME_LENGTH];
    char command[512];

    printf("Enter the path to the PDF file you want to upload: ");
    if (fgets(filename, sizeof(filename), stdin) == NULL) {
        perror("Failed to read input");
        return EXIT_FAILURE;
    }

    // Remove newline character from filename
    size_t len = strlen(filename);
    if (len > 0 && filename[len - 1] == '\n') {
        filename[len - 1] = '\0';
    }

    // Check if the file has a .pdf extension
    const char *ext = strrchr(filename, '.');
    if (!ext || strcmp(ext, ".pdf") != 0) {
        fprintf(stderr, "Error: The file must have a .pdf extension.\n");
        return EXIT_FAILURE;
    }

    // Create the command to copy the file to the uploads directory
    snprintf(command, sizeof(command), "cp \"%s\" \"%s\"", filename, UPLOADS_DIR);

    // Execute the command
    if (system(command) != 0) {
        perror("Failed to upload file");
        return EXIT_FAILURE;
    }

    printf("File uploaded successfully.\n");
    return EXIT_SUCCESS;
}