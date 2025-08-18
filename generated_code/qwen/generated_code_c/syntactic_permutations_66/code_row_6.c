#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define UPLOADS_DIR "uploads/"

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    const char *input_filename = argv[1];
    char output_path[FILENAME_MAX];

    snprintf(output_path, sizeof(output_path), "%s%s", UPLOADS_DIR, input_filename);

    FILE *source_file = fopen(input_filename, "rb");
    if (!source_file) {
        perror("Failed to open source file");
        return 1;
    }

    FILE *destination_file = fopen(output_path, "wb");
    if (!destination_file) {
        perror("Failed to open destination file");
        fclose(source_file);
        return 1;
    }

    char buffer[4096];
    size_t bytes_read;

    while ((bytes_read = fread(buffer, 1, sizeof(buffer), source_file)) > 0) {
        if (fwrite(buffer, 1, bytes_read, destination_file) != bytes_read) {
            perror("Failed to write to destination file");
            fclose(source_file);
            fclose(destination_file);
            return 1;
        }
    }

    if (ferror(source_file)) {
        perror("Error reading source file");
        fclose(source_file);
        fclose(destination_file);
        return 1;
    }

    fclose(source_file);
    fclose(destination_file);

    printf("File saved to %s\n", output_path);

    return 0;
}