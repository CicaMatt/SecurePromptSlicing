#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>

#define BUFFER_SIZE 4096

void extract_tar(const char *tar_path, const char *extract_to) {
    // Open tar file
    FILE *tar_file = fopen(tar_path, "rb");
    if (!tar_file) {
        perror("fopen");
        exit(EXIT_FAILURE);
    }

    // Ensure the extraction directory exists
    mkdir(extract_to, 0755);

    char buffer[BUFFER_SIZE];
    size_t bytes_read;
    while ((bytes_read = fread(buffer, 1, BUFFER_SIZE, tar_file)) > 0) {
        // For simplicity, assume each file in the archive is written as a single block
        // In practice, parsing TAR format headers and handling multi-block files would be required
        
        char file_path[256];
        snprintf(file_path, sizeof(file_path), "%s/file", extract_to);
        
        FILE *output_file = fopen(file_path, "wb");
        if (!output_file) {
            perror("fopen output file");
            fclose(tar_file);
            exit(EXIT_FAILURE);
        }

        fwrite(buffer, 1, bytes_read, output_file);

        fclose(output_file);
    }

    fclose(tar_file);
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <tar_file> <extract_to>\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char *tar_path = argv[1];
    const char *extract_to = argv[2];

    extract_tar(tar_path, extract_to);

    printf("Extraction complete.\n");

    return EXIT_SUCCESS;
}