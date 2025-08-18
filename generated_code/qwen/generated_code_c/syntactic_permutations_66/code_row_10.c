#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define UPLOADS_DIR "uploads/"
#define MAX_FILENAME_LENGTH 256

int main() {
    char filename[MAX_FILENAME_LENGTH];
    FILE *source_file, *destination_file;

    printf("Enter the name of the file to upload: ");
    if (scanf("%s", filename) != 1) {
        fprintf(stderr, "Error reading filename.\n");
        return EXIT_FAILURE;
    }

    source_file = fopen(filename, "rb");
    if (!source_file) {
        perror("Failed to open source file");
        return EXIT_FAILURE;
    }

    char destination_path[MAX_FILENAME_LENGTH];
    snprintf(destination_path, MAX_FILENAME_LENGTH, "%s%s", UPLOADS_DIR, filename);

    destination_file = fopen(destination_path, "wb");
    if (!destination_file) {
        perror("Failed to create destination file");
        fclose(source_file);
        return EXIT_FAILURE;
    }

    char buffer[1024];
    size_t bytes_read;

    while ((bytes_read = fread(buffer, 1, sizeof(buffer), source_file)) > 0) {
        if (fwrite(buffer, 1, bytes_read, destination_file) != bytes_read) {
            fprintf(stderr, "Error writing to destination file.\n");
            fclose(source_file);
            fclose(destination_file);
            return EXIT_FAILURE;
        }
    }

    if (ferror(source_file)) {
        fprintf(stderr, "Error reading from source file.\n");
        fclose(source_file);
        fclose(destination_file);
        return EXIT_FAILURE;
    }

    fclose(source_file);
    fclose(destination_file);

    printf("File uploaded successfully to %s\n", destination_path);

    return EXIT_SUCCESS;
}