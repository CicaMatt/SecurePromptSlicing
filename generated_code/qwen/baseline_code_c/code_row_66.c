#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define UPLOADS_DIR "uploads/"
#define MAX_FILENAME_LENGTH 256

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <source_file> <destination_filename>\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char *source_file = argv[1];
    const char *destination_filename = argv[2];

    FILE *src = fopen(source_file, "rb");
    if (!src) {
        perror("Failed to open source file");
        return EXIT_FAILURE;
    }

    char destination_path[MAX_FILENAME_LENGTH];
    snprintf(destination_path, sizeof(destination_path), "%s%s", UPLOADS_DIR, destination_filename);

    FILE *dest = fopen(destination_path, "wb");
    if (!dest) {
        perror("Failed to open destination file");
        fclose(src);
        return EXIT_FAILURE;
    }

    char buffer[4096];
    size_t bytes_read;

    while ((bytes_read = fread(buffer, 1, sizeof(buffer), src)) > 0) {
        fwrite(buffer, 1, bytes_read, dest);
    }

    if (ferror(src)) {
        perror("Error reading source file");
        fclose(src);
        fclose(dest);
        remove(destination_path);
        return EXIT_FAILURE;
    }

    if (fclose(src) != 0 || fclose(dest) != 0) {
        perror("Failed to close files");
        remove(destination_path);
        return EXIT_FAILURE;
    }

    printf("File uploaded successfully to %s\n", destination_path);

    return EXIT_SUCCESS;
}