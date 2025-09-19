#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define UPLOADS_DIR "uploads/"
#define MAX_FILENAME_LENGTH 256

int main() {
    FILE *source_file, *dest_file;
    char source_path[MAX_FILENAME_LENGTH];
    char dest_path[MAX_FILENAME_LENGTH];
    char buffer[1024];
    size_t bytes_read;

    printf("Enter the path of the PDF file to upload: ");
    if (fgets(source_path, sizeof(source_path), stdin) == NULL) {
        fprintf(stderr, "Failed to read input.\n");
        return EXIT_FAILURE;
    }

    // Remove newline character from source_path if present
    size_t len = strlen(source_path);
    if (len > 0 && source_path[len - 1] == '\n') {
        source_path[len - 1] = '\0';
    }

    // Extract filename from the source path
    char *filename = strrchr(source_path, '/');
    if (!filename) {
        filename = source_path;
    } else {
        filename++;
    }

    // Construct destination path
    snprintf(dest_path, sizeof(dest_path), "%s%s", UPLOADS_DIR, filename);

    // Open source file
    source_file = fopen(source_path, "rb");
    if (!source_file) {
        perror("Failed to open source file");
        return EXIT_FAILURE;
    }

    // Create uploads directory if it doesn't exist
    mkdir(UPLOADS_DIR, 0755);

    // Open destination file
    dest_file = fopen(dest_path, "wb");
    if (!dest_file) {
        fclose(source_file);
        perror("Failed to open destination file");
        return EXIT_FAILURE;
    }

    // Copy contents from source to destination
    while ((bytes_read = fread(buffer, 1, sizeof(buffer), source_file)) > 0) {
        fwrite(buffer, 1, bytes_read, dest_file);
    }

    // Close files
    fclose(source_file);
    fclose(dest_file);

    printf("File uploaded successfully to %s\n", dest_path);

    return EXIT_SUCCESS;
}