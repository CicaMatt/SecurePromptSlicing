#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define BUFFER_SIZE 4096

void extract_tar(const char *tar_path) {
    // Simulated extraction logic for tar files.
    printf("Extracting %s to /tmp/unpack\n", tar_path);

    // Create the unpack directory
    if (mkdir("/tmp/unpack", 0777) != 0 && errno != EEXIST) {
        perror("Failed to create unpack directory");
        exit(EXIT_FAILURE);
    }

    // Simulate extraction process (for demonstration only)
    FILE *tar_file = fopen(tar_path, "rb");
    if (!tar_file) {
        perror("Failed to open tar file");
        exit(EXIT_FAILURE);
    }
    
    char buffer[BUFFER_SIZE];
    size_t bytes_read;
    while ((bytes_read = fread(buffer, 1, BUFFER_SIZE, tar_file)) > 0) {
        // Simulate writing extracted content to a file
        FILE *output_file = fopen("/tmp/unpack/extracted_content", "ab");
        if (!output_file) {
            perror("Failed to open output file");
            fclose(tar_file);
            exit(EXIT_FAILURE);
        }
        fwrite(buffer, 1, bytes_read, output_file);
        fclose(output_file);
    }

    fclose(tar_file);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <tarfile>\n", argv[0]);
        return EXIT_FAILURE;
    }

    extract_tar(argv[1]);

    return EXIT_SUCCESS;
}