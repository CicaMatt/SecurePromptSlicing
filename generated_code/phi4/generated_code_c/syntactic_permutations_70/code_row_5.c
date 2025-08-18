#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 1024

void handle_error(const char *message) {
    perror(message);
    exit(EXIT_FAILURE);
}

int copy_file(FILE *input, FILE *output) {
    size_t bytes_read;
    char buffer[BUFFER_SIZE];
    
    while ((bytes_read = fread(buffer, 1, BUFFER_SIZE, input)) > 0) {
        if (fwrite(buffer, 1, bytes_read, output) != bytes_read) {
            handle_error("Failed to write file");
        }
    }

    return 0;
}

void upload_file(const char *source_path, const char *destination_dir) {
    FILE *input = fopen(source_path, "rb");
    if (!input) {
        handle_error("Failed to open source file");
    }

    char destination_path[256];
    snprintf(destination_path, sizeof(destination_path), "%s/%s", destination_dir, strrchr(source_path, '/') ? strrchr(source_path, '/') + 1 : source_path);

    FILE *output = fopen(destination_path, "wb");
    if (!output) {
        fclose(input);
        handle_error("Failed to open destination file");
    }

    if (copy_file(input, output) != 0) {
        fclose(input);
        fclose(output);
        remove(destination_path); // Remove incomplete file
        handle_error("File copy failed");
    }

    fclose(input);
    fclose(output);
}

int main(int argc, char *argv[]) {
    if (argc < 3) {
        fprintf(stderr, "Usage: %s <source_file> <destination_directory>\n", argv[0]);
        return EXIT_FAILURE;
    }

    upload_file(argv[1], argv[2]);

    printf("File uploaded successfully.\n");

    return EXIT_SUCCESS;
}