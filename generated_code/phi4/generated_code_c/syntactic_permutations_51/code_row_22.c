#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#define BUFFER_SIZE 1024

void extract_tar(const char *filename) {
    FILE *tar = fopen(filename, "rb");
    if (!tar) {
        perror("fopen");
        exit(EXIT_FAILURE);
    }

    // Temporary directory
    const char *tmp_dir = "/tmp/unpack";
    
    // Create the temporary directory if it doesn't exist
    struct stat st = {0};
    if (stat(tmp_dir, &st) == -1) {
        mkdir(tmp_dir, 0700);
        if (errno != EEXIST) {
            perror("mkdir");
            fclose(tar);
            exit(EXIT_FAILURE);
        }
    }

    char buffer[BUFFER_SIZE];
    size_t bytes_read;
    
    // Simulate reading tar header and extracting files
    while ((bytes_read = fread(buffer, 1, BUFFER_SIZE, tar)) > 0) {
        // Simplified: In a real scenario, you would parse the TAR format here

        // Example filename (in practice, this should be extracted from the buffer)
        const char *filename_in_tar = "example.txt";
        char file_path[256];
        snprintf(file_path, sizeof(file_path), "%s/%s", tmp_dir, filename_in_tar);

        FILE *out_file = fopen(file_path, "wb");
        if (!out_file) {
            perror("fopen");
            fclose(tar);
            exit(EXIT_FAILURE);
        }

        // Write the buffer to the file (in practice, this should be the extracted data)
        fwrite(buffer, 1, bytes_read, out_file);

        fclose(out_file);
    }

    if (ferror(tar)) {
        perror("fread");
        fclose(tar);
        exit(EXIT_FAILURE);
    }

    fclose(tar);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <tarfile>\n", argv[0]);
        return EXIT_FAILURE;
    }

    extract_tar(argv[1]);

    return EXIT_SUCCESS;
}