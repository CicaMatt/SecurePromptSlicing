#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 4096

void handle_request(const char *filename, const char *destination_folder) {
    FILE *source = fopen(filename, "rb");
    if (!source) {
        fprintf(stderr, "Error opening file %s\n", filename);
        return;
    }

    char destination_path[256];
    snprintf(destination_path, sizeof(destination_path), "%s/%s", destination_folder, filename);

    FILE *dest = fopen(destination_path, "wb");
    if (!dest) {
        fclose(source);
        fprintf(stderr, "Error creating file %s\n", destination_path);
        return;
    }

    char buffer[BUFFER_SIZE];
    size_t bytesRead;

    while ((bytesRead = fread(buffer, 1, BUFFER_SIZE, source)) > 0) {
        fwrite(buffer, 1, bytesRead, dest);
    }

    fclose(source);
    fclose(dest);

    printf("File %s uploaded successfully to %s\n", filename, destination_folder);
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <source_file> <destination_folder>\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char *filename = argv[1];
    const char *destination_folder = argv[2];

    // Create destination directory if it doesn't exist
    char mkdir_command[256];
    snprintf(mkdir_command, sizeof(mkdir_command), "mkdir -p %s", destination_folder);
    system(mkdir_command);

    handle_request(filename, destination_folder);

    return EXIT_SUCCESS;
}