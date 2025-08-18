#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

// Function declarations for tarfile and open operations.
int extract_tar(const char *tar_path, const char *dest_dir);
FILE* safe_open_file(const char *filename, const char *mode);

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <tarfile> <destination_directory>\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char *tar_path = argv[1];
    const char *dest_dir = argv[2];

    // Extract tar file to destination directory
    if (extract_tar(tar_path, dest_dir) != 0) {
        fprintf(stderr, "Failed to extract tar file: %s\n", tar_path);
        return EXIT_FAILURE;
    }

    printf("Extraction completed successfully.\n");
    return EXIT_SUCCESS;
}

int extract_tar(const char *tar_path, const char *dest_dir) {
    // This is a placeholder implementation for extracting tar files.
    // A real-world scenario would require using system calls or third-party libraries
    // to handle different compression methods like gzip or bz2.

    FILE *tar_file = safe_open_file(tar_path, "rb");
    if (!tar_file) {
        perror("Error opening tar file");
        return EXIT_FAILURE;
    }

    char command[512];
    snprintf(command, sizeof(command), "mkdir -p %s && cd %s && tar xf ../%s", dest_dir, dest_dir, tar_path);
    
    int result = system(command);
    fclose(tar_file);

    if (result != 0) {
        fprintf(stderr, "Failed to extract tar file using command: %s\n", command);
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

FILE* safe_open_file(const char *filename, const char *mode) {
    FILE *file = fopen(filename, mode);
    if (!file) {
        perror("Error opening file");
    }
    return file;
}