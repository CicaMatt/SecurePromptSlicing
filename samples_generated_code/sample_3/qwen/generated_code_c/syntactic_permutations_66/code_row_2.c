#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define UPLOADS_DIR "uploads/"
#define MAX_FILENAME_LEN 256

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <source_pdf> <destination_filename>\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char *source_file = argv[1];
    const char *dest_filename = argv[2];

    // Ensure the uploads directory exists
    if (access(UPLOADS_DIR, F_OK) == -1) {
        mkdir(UPLOADS_DIR, 0755);
    }

    char dest_path[MAX_FILENAME_LEN];
    snprintf(dest_path, sizeof(dest_path), "%s%s", UPLOADS_DIR, dest_filename);

    FILE *source = fopen(source_file, "rb");
    if (!source) {
        perror("Failed to open source file");
        return EXIT_FAILURE;
    }

    FILE *dest = fopen(dest_path, "wb");
    if (!dest) {
        perror("Failed to open destination file");
        fclose(source);
        return EXIT_FAILURE;
    }

    char buffer[4096];
    size_t bytesRead;

    while ((bytesRead = fread(buffer, 1, sizeof(buffer), source)) > 0) {
        fwrite(buffer, 1, bytesRead, dest);
    }

    if (ferror(source)) {
        perror("Error reading from source file");
        fclose(source);
        fclose(dest);
        unlink(dest_path); // Remove the partially written file
        return EXIT_FAILURE;
    }

    fclose(source);
    fclose(dest);

    printf("File successfully uploaded to %s\n", dest_path);
    return EXIT_SUCCESS;
}